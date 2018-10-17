#pragma once
#include <SDL_opengl.h>
#include "ComponentSystem.h"

struct TextureComponent
{
	struct Aos
	{
		GLuint texture;
		float width, height;
	};
	struct Soa
	{
		GLuint* texture;
		float *width, *height;
	};
};

DEFINE_SOA_CLASS(TextureComponent, 3)
DEFINE_SOA_TYPE(TextureComponent,0,GLuint,texture)
DEFINE_SOA_TYPE(TextureComponent,1,float,width)
DEFINE_SOA_TYPE(TextureComponent,2,float,height)

class TextureComponentSystem : public ComponentSystem<TextureComponent>
{
public:
	TextureComponentSystem();

	void OnUpdate(TextureComponent::Soa* component, size_t entity) override;
	void OnLateUpdate(TextureComponent::Soa* component, size_t entity) override;
	void OnCleanUp(TextureComponent::Soa* component) override;

private:
};
