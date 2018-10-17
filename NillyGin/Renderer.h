#pragma once

#include <SDL.h>
#include <SDL_opengl.h>
#include <GL/GLU.h>
#include <SDL_image.h>
#include "Singleton.h"

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

struct Float2
{
	Float2(float x, float y)
		:x(x), y(y)
	{
	}

	float x, y;
};

class Renderer : public Singleton<Renderer>
{
public:
	Renderer() = default;

	void Initialize();
	void CleanUp();

	void Display();
	void ClearBackground();

	void DrawRectangle(float x, float y, float width, float height,Colour colour, bool filled = true);
	void DrawTriangle(Float2 p1, Float2 p2, Float2 p3, Colour colour, bool filled = true);
	void DrawEllipse(Float2 center, float width, float height, Colour colour, float interpolation = 30.f,bool filled = true);
	void DrawLine(Float2 p1, Float2 p2, Colour colour, float lineWidth = 1.f);
	void DrawPoint(Float2 point, Colour colour, float pointSize = 1.f);

private:
	SDL_Window* m_pWindow;
	SDL_GLContext m_GlContext;
};