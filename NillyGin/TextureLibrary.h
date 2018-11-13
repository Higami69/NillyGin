#pragma once
#include <vector>
#include <SDL.h>
#include <SDL_opengl.h>

class TextureLibrary
{
public:
	TextureLibrary() = default;

	GLuint LoadTexture(const std::string& filePath, GLint scaleMode);
	void FreeTextures();

private:
	std::vector<SDL_Surface*> m_pTexSurfaces;
};
