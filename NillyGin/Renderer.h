#pragma once

#include <SDL.h>
#include <SDL_opengl.h>
#include <GL/GLU.h>
#include <SDL_image.h>
#include "Singleton.h"
#include <string>

#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")
#pragma comment (lib,"opengl32.lib")
#pragma comment (lib,"Glu32.lib")
#pragma comment(lib, "SDL2_image.lib")  



//class Renderer : public Singleton<Renderer>
//{
//public:
//	Renderer() = default;
//
//	void Initialize();
//	void CleanUp();
//
//	void Display();
//	void ClearBackground();
//
//	void DrawRectangle(float x, float y, float width, float height,Colour colour, bool filled = true);
//	void DrawTriangle(Float2 p1, Float2 p2, Float2 p3, Colour colour, bool filled = true);
//	void DrawEllipse(Float2 center, float width, float height, Colour colour, float interpolation = 30.f,bool filled = true);
//	void DrawLine(Float2 p1, Float2 p2, Colour colour, float lineWidth = 1.f);
//	void DrawPoint(Float2 point, Colour colour, float pointSize = 1.f);
//
//	void DrawTexture(GLuint texture, Float2 botLeft, float width, float height);
//
//	GLuint LoadTexture(const std::string& path, GLint scaleMode = GL_LINEAR);
//
//private:
//	SDL_Window* m_pWindow;
//	SDL_GLContext m_GlContext;
//};