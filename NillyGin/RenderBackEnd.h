#pragma once
#include <thread>
#include <SDL.h>
#include <SDL_opengl.h>
#include <GL/GLU.h>

struct RenderTaskBuffer;

class RenderBackEnd
{
public:
	RenderBackEnd() = default;

	void Initialize();
	void CleanUp();

	void Update();
	void SetNextBuffer(RenderTaskBuffer* buffer);

	SDL_GLContext GetContext() const;
	SDL_Window* GetWindow() const;
private:
	void InitializeThread();
	void UpdateThread();
	void CleanUpThread();

	SDL_Window* m_pWindow = nullptr;
	SDL_GLContext m_GlContext;
	std::thread m_RenderThread;

	RenderTaskBuffer *m_pCurrentBuffer, *m_pNextBuffer; //TODO: Change to queue of buffers?
};
