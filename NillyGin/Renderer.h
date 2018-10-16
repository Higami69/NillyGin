#pragma once

#include <SDL.h>
#include <SDL_opengl.h>
#include <GL/GLU.h>
#include <SDL_image.h>

#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")
#pragma comment (lib,"opengl32.lib")
#pragma comment (lib,"Glu32.lib")
#pragma comment(lib, "SDL2_image.lib")  

struct Colour
{
	Colour(float r, float g, float b, float a)
		:r{r}, g{g}, b{b}, a{a}
	{
	}

	float r, g, b, a;
};

class Renderer
{
public:
	Renderer() = default;

	void Initialize();
	void CleanUp();

	void Display();
	void ClearBackground();

	void DrawRectangle(float x, float y, float width, float height,Colour colour);

private:
	SDL_Window* m_pWindow;
	SDL_GLContext m_GlContext;
};