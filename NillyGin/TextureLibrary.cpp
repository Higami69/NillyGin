#include "pch.h"
#include "TextureLibrary.h"
#include <SDL_image.h>

GLuint TextureLibrary::LoadTexture(const std::string& filePath, GLint scaleMode)
{
	GLuint texId;
	auto surface = IMG_Load(filePath.c_str());
	m_pTexSurfaces.push_back(surface);

	//Generate and bind texture
	glGenTextures(1, &texId);
	glBindTexture(GL_TEXTURE_2D, texId);
	
	//Check pixel format
	switch(surface->format->BytesPerPixel)
	{
	case 1:
		//TODO: Implement later
		break;
	case 2:
		//TODO:Implement later
		break;
	case 3:
		//TODO: Implement later
		break;
	case 4:
		if(surface->format->Rmask == 0x000000ff) //RGBA
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
		}
		else //BGRA
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, surface->pixels);
		}
		break;
	}
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, scaleMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, scaleMode);
	
	return texId;
}

void TextureLibrary::FreeTextures()
{
	for(auto surface : m_pTexSurfaces)
	{
		SDL_FreeSurface(surface);
	}

	m_pTexSurfaces.clear();
}
