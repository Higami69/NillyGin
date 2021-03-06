#include "pch.h"
//#include "Renderer.h"
//#include <iostream>
//
//#define DEGREES_TO_RADIANS float(M_PI / 180.f)
//
//void Renderer::Initialize()
//{
//	SDL_Init(SDL_INIT_VIDEO);
//
//	m_pWindow = SDL_CreateWindow("NillyGin", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
//
//	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
//	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
//	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
//
//	m_GlContext = SDL_GL_CreateContext(m_pWindow);
//
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//
//	gluOrtho2D(0, 640, 0, 480);
//	glViewport(0, 0, 640, 480);
//
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//
//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//
//	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
//}
//
//void Renderer::CleanUp()
//{
//	IMG_Quit();
//	SDL_GL_DeleteContext(m_GlContext);
//	SDL_DestroyWindow(m_pWindow);
//	SDL_Quit();
//}
//
//void Renderer::Display()
//{
//	SDL_GL_SwapWindow(m_pWindow);
//}
//
//void Renderer::ClearBackground()
//{
//	glClearColor(0.f, 0.f, 0.f, 1.f);
//	glClear(GL_COLOR_BUFFER_BIT);
//}
//
//void Renderer::DrawRectangle(float x, float y, float width, float height,Colour colour, bool filled)
//{
//	glColor4f(colour.r,colour.g,colour.b,colour.a);
//
//	if (filled) glBegin(GL_QUADS);
//	else glBegin(GL_LINE_LOOP);
//
//	glVertex2f(x, y);
//	glVertex2f(x + width, y);
//	glVertex2f(x + width, y + height);
//	glVertex2f(x, y + height);
//
//	glEnd();
//}
//
//void Renderer::DrawTriangle(Float2 p1, Float2 p2, Float2 p3, Colour colour, bool filled)
//{
//	glColor4f(colour.r, colour.g, colour.b, colour.a);
//
//	if (filled) glBegin(GL_TRIANGLES);
//	else glBegin(GL_LINE_LOOP);
//
//	glVertex2f(p1.x, p1.y);
//	glVertex2f(p2.x, p2.y);
//	glVertex2f(p3.x, p3.y);
//
//	glEnd();
//}
//
//void Renderer::DrawEllipse(Float2 center, float width, float height, Colour colour, float interpolation, bool filled)
//{
//	glColor4f(colour.r, colour.g, colour.b, colour.a);
//
//	if (filled) glBegin(GL_POLYGON);
//	else glBegin(GL_LINE_LOOP);
//
//	for (int i = 0; i < 360; i += (int)interpolation) glVertex2f(center.x + width*cosf(i * DEGREES_TO_RADIANS), center.y + height*sinf(i * DEGREES_TO_RADIANS));
//
//	glEnd();
//}
//
//void Renderer::DrawLine(Float2 p1, Float2 p2, Colour colour, float lineWidth)
//{
//	glColor4f(colour.r, colour.g, colour.b, colour.a);
//	glLineWidth(lineWidth);
//
//	glBegin(GL_LINE);
//
//	glVertex2f(p1.x, p1.y);
//	glVertex2f(p2.x, p2.y);
//
//	glEnd();
//}
//
//void Renderer::DrawPoint(Float2 point, Colour colour, float pointSize)
//{
//	glColor4f(colour.r, colour.g, colour.b, colour.a);
//	glPointSize(pointSize);
//
//	glBegin(GL_POINT);
//
//	glVertex2f(point.x, point.y);
//
//	glEnd();
//
//}
//
//void Renderer::DrawTexture(GLuint texture, Float2 botLeft, float width, float height)
//{
//	glBindTexture(GL_TEXTURE_2D, texture);
//	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
//
//	glEnable(GL_TEXTURE_2D);
//	{
//		glBegin(GL_QUADS);
//
//		glTexCoord2f(0, 0);
//		glVertex2f(botLeft.x, botLeft.y + height);
//
//		glTexCoord2f(1, 0);
//		glVertex2f(botLeft.x + width, botLeft.y + height);
//
//		glTexCoord2f(1, 1);
//		glVertex2f(botLeft.x + width, botLeft.y);
//
//		glTexCoord2f(0, 1);
//		glVertex2f(botLeft.x, botLeft.y);
//	
//		glEnd();
//	}
//	glDisable(GL_TEXTURE_2D);
//}
//
//GLuint Renderer::LoadTexture(const std::string& path, GLint scaleMode)
//{
//	GLuint texture;
//	auto surface = IMG_Load(path.c_str());
//
//	//Generate and bind texture
//	glGenTextures(1, &texture);
//	glBindTexture(GL_TEXTURE_2D, texture);
//
//	//Check pixel format
//	switch(surface->format->BytesPerPixel)
//	{
//	case 1:
//		//TODO: Implement later
//		break;
//	case 2:
//		//TODO:Implement later
//		break;
//	case 3:
//		//TODO: Implement later
//		break;
//	case 4:
//		if(surface->format->Rmask == 0x000000ff) //RGBA
//		{
//			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
//		}
//		else //BGRA
//		{
//			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, surface->pixels);
//		}
//		break;
//	}
//
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, scaleMode);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, scaleMode);
//
//	auto e = SDL_GetError();
//
//	return texture;
//}
