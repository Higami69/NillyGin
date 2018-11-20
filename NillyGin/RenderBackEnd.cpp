#include "pch.h"
#include "RenderBackEnd.h"
#include <SDL_image.h>
#include "RenderQueue.h"

void RenderBackEnd::Initialize()
{
	SDL_Init(SDL_INIT_VIDEO);

	m_pWindow = SDL_CreateWindow("NillyGin", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

	m_RenderThread = std::thread(&RenderBackEnd::InitializeThread, this);
	m_RenderThread.join();
}

void RenderBackEnd::CleanUp()
{
	m_RenderThread.join();
	m_RenderThread = std::thread(&RenderBackEnd::CleanUpThread, this);
	m_RenderThread.join();

	IMG_Quit();
	SDL_DestroyWindow(m_pWindow);
	SDL_Quit();
}

void RenderBackEnd::Update()
{
	if(m_RenderThread.joinable()) m_RenderThread.join();

	if (m_pCurrentBuffer != nullptr)
	{
		m_pCurrentBuffer->Free();
	}

	m_pCurrentBuffer = m_pNextBuffer;
	m_pNextBuffer = nullptr;

	m_RenderThread = std::thread(&RenderBackEnd::UpdateThread, this);
}

void RenderBackEnd::SetNextBuffer(RenderTaskBuffer* buffer)
{
	m_pNextBuffer = buffer;
}

void RenderBackEnd::SetPersistentBuffer(RenderTaskBuffer* buffer)
{
	m_pPersistentBuffer = buffer;
}

SDL_GLContext RenderBackEnd::GetContext() const
{
	return m_GlContext;
}

SDL_Window* RenderBackEnd::GetWindow() const
{
	return m_pWindow;
}

void RenderBackEnd::InitializeThread()
{
	m_GlContext = SDL_GL_CreateContext(m_pWindow);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(0, 640, 0, 480);
	glViewport(0, 0, 640, 480);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_TRUE);

	SDL_GL_MakeCurrent(0, 0);
}

void RenderBackEnd::UpdateThread()
{
	//Set context
	SDL_GL_MakeCurrent(m_pWindow, m_GlContext);

	//Clear buffer
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if(m_pPersistentBuffer != nullptr)
	{
		DrawBuffer(m_pPersistentBuffer);
	}
	if (m_pCurrentBuffer != nullptr)
	{
		DrawBuffer(m_pCurrentBuffer);
	}

	//Present and release context
	SDL_GL_SwapWindow(m_pWindow);
	SDL_GL_MakeCurrent(0, 0);
}

void RenderBackEnd::CleanUpThread()
{
	SDL_GL_DeleteContext(m_GlContext);
}

void RenderBackEnd::DrawBuffer(RenderTaskBuffer* buffer)
{
	//Render points
	glEnable(GL_POINT_SMOOTH);
	for (size_t i = 0; i < buffer->pointTasks.GetSize(); i++)
	{
		auto data = buffer->pointTasks.GetAos(i);
		glPointSize(data.pointSize);
		glBegin(GL_POINTS);
		glColor4f(data.colour.r, data.colour.g, data.colour.b, data.colour.a);
		glVertex3f(data.point.x, data.point.y, data.point.z);
		glEnd();
	}
	glDisable(GL_POINT_SMOOTH);

	//Render lines
	glEnable(GL_LINE_SMOOTH);
	for (size_t i = 0; i < buffer->lineTasks.GetSize(); i++)
	{
		auto data = buffer->lineTasks.GetAos(i);
		glLineWidth(data.lineWidth);
		glBegin(GL_LINES);
		glColor4f(data.colour.r, data.colour.g, data.colour.b, data.colour.a);
		glVertex3f(data.point1.x, data.point1.y, data.depth);
		glVertex3f(data.point2.x, data.point2.y, data.depth);
		glEnd();
	}

	//Render empty triangles
	for (size_t i = 0; i < buffer->triangleTasks.GetSize(); i++)
	{
		auto data = buffer->triangleTasks.GetAos(i);
		glLineWidth(data.lineWidth);
		glBegin(GL_LINE_LOOP);
		glColor4f(data.colour.r, data.colour.g, data.colour.b, data.colour.a);
		glVertex3f(data.point1.x, data.point1.y, data.depth);
		glVertex3f(data.point2.x, data.point2.y, data.depth);
		glVertex3f(data.point3.x, data.point3.y, data.depth);
		glEnd();
	}

	//Render empty rectangles
	for (size_t i = 0; i < buffer->rectangleTasks.GetSize(); i++)
	{
		auto data = buffer->rectangleTasks.GetAos(i);
		glLineWidth(data.lineWidth);
		glBegin(GL_LINE_LOOP);
		glColor4f(data.colour.r, data.colour.g, data.colour.b, data.colour.a);
		glVertex3f(data.bottomLeft.x, data.bottomLeft.y, data.depth);
		glVertex3f(data.bottomLeft.x + data.dimensions.x, data.bottomLeft.y, data.depth);
		glVertex3f(data.bottomLeft.x + data.dimensions.x, data.bottomLeft.y + data.dimensions.y, data.depth);
		glVertex3f(data.bottomLeft.x, data.bottomLeft.y + data.dimensions.y, data.depth);
		glEnd();
	}

	//Render empty ellipses
	for (size_t i = 0; i < buffer->ellipseTasks.GetSize(); i++)
	{
		auto data = buffer->ellipseTasks.GetAos(i);
		auto stepSize = 360.f / data.nrSections;
		glBegin(GL_LINE_LOOP);
		glColor4f(data.colour.r, data.colour.g, data.colour.b, data.colour.a);
		for (float f = 0; f < 360.f; f += stepSize)
		{
			glVertex3f(data.center.x + (data.dimensions.x*cosf(f*DEGREES_TO_RADIANS)), data.center.y + (data.dimensions.y*sinf(f*DEGREES_TO_RADIANS))
				, data.depth);
		}
		glEnd();
	}
	glDisable(GL_LINE_SMOOTH);

	//Render filled triangles
	glBegin(GL_TRIANGLES);
	for (size_t i = 0; i < buffer->filledTriangleTasks.GetSize(); i++)
	{
		auto data = buffer->filledTriangleTasks.GetAos(i);
		glColor4f(data.colour.r, data.colour.g, data.colour.b, data.colour.a);
		glVertex3f(data.point1.x, data.point1.y, data.depth);
		glVertex3f(data.point2.x, data.point2.y, data.depth);
		glVertex3f(data.point3.x, data.point3.y, data.depth);
	}
	glEnd();

	//Render filled rectangles
	glBegin(GL_QUADS);
	for (size_t i = 0; i < buffer->filledRectangleTasks.GetSize(); i++)
	{
		auto data = buffer->filledRectangleTasks.GetAos(i);
		glColor4f(data.colour.r, data.colour.g, data.colour.b, data.colour.a);
		glVertex3f(data.bottomLeft.x, data.bottomLeft.y, data.depth);
		glVertex3f(data.bottomLeft.x + data.dimensions.x, data.bottomLeft.y, data.depth);
		glVertex3f(data.bottomLeft.x + data.dimensions.x, data.bottomLeft.y + data.dimensions.y, data.depth);
		glVertex3f(data.bottomLeft.x, data.bottomLeft.y + data.dimensions.y, data.depth);
	}
	glEnd();

	//Render filled ellipses
	for (size_t i = 0; i < buffer->filledEllipseTasks.GetSize(); i++)
	{
		auto data = buffer->filledEllipseTasks.GetAos(i);
		auto stepSize = 360.f / data.nrSections;
		glBegin(GL_POLYGON);
		glColor4f(data.colour.r, data.colour.g, data.colour.b, data.colour.a);
		for (float f = 0; f < 360.f; f += stepSize)
		{
			glVertex3f(data.center.x + (data.dimensions.x*cosf(f*DEGREES_TO_RADIANS)), data.center.y + (data.dimensions.y*sinf(f*DEGREES_TO_RADIANS))
				, data.depth);
		}
		glEnd();
	}

	//Render textures

	glColor4f(1.f, 1.f, 1.f, 1.f);
	for (size_t i = 0; i < buffer->textureTasks.GetSize(); i++)
	{
		auto data = buffer->textureTasks.GetAos(i);
		
		glBindTexture(GL_TEXTURE_2D, data.texId);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);

		glTexCoord3f(0, 1, 1);
		glVertex3f(data.botLeft.x, data.botLeft.y, data.depth);
		glTexCoord3f(1, 1, 1);
		glVertex3f(data.botLeft.x + data.dimensions.x, data.botLeft.y, data.depth);
		glTexCoord3f(1, 0, 1);
		glVertex3f(data.botLeft.x + data.dimensions.x, data.botLeft.y + data.dimensions.y, data.depth);
		glTexCoord3f(0, 0, 1);
		glVertex3f(data.botLeft.x, data.botLeft.y + data.dimensions.y, data.depth);

		glDisable(GL_TEXTURE_2D);
		glEnd();
	}
}
