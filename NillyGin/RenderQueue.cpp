#include "pch.h"
#include "RenderQueue.h"
#include "RenderBackEnd.h"

void RenderTaskBuffer::Free()
{
	pointTasks.Free();
	lineTasks.Free();
	rectangleTasks.Free();
	filledRectangleTasks.Free();
	ellipseTasks.Free();
	filledEllipseTasks.Free();
	triangleTasks.Free();
	filledTriangleTasks.Free();
	textureTasks.Free();
}

RenderQueue::RenderQueue()
{
	m_pFrontBuffer = new RenderTaskBuffer();
	m_pBackBuffer = new RenderTaskBuffer();
}

RenderQueue::~RenderQueue()
{
	m_pFrontBuffer->Free();
	m_pBackBuffer->Free();
	delete m_pFrontBuffer;
	m_pFrontBuffer = nullptr;
	delete m_pBackBuffer;
	m_pBackBuffer = nullptr;
}

void RenderQueue::Initialize(RenderBackEnd* backEnd)
{
	m_pRenderBackEnd = backEnd;
}

void RenderQueue::Flush()
{
	if(m_FrontBufferActive)
	{
		m_pRenderBackEnd->SetNextBuffer(m_pFrontBuffer);
	}
	else
	{
		m_pRenderBackEnd->SetNextBuffer(m_pBackBuffer);
	}

	m_FrontBufferActive = !m_FrontBufferActive;
}

