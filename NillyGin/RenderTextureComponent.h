#pragma once
#include "Structs.h"
#include "ComponentSystem.h"
#include <SDL_opengl.h>

struct RenderTextureComponent
{
	struct Aos
	{
		Float2::Aos offset, dimensions;
		GLuint texId;
	};
	struct Soa
	{
		Float2::Soa *offset, *dimensions;
		GLuint *texId;
	};
};

DEFINE_SOA_CLASS(RenderTextureComponent, 5, 2)
DEFINE_SOA_STRUCT(RenderTextureComponent, 0, Float2::Soa, offset)
DEFINE_SOA_STRUCT(RenderTextureComponent, 1, Float2::Soa, dimensions)
DEFINE_SOA_TYPE_STRUCT(RenderTextureComponent, 0, Float2, float, offset, x)
DEFINE_SOA_TYPE_STRUCT(RenderTextureComponent, 1, Float2, float, offset, y)
DEFINE_SOA_TYPE_STRUCT(RenderTextureComponent, 2, Float2, float, dimensions, x)
DEFINE_SOA_TYPE_STRUCT(RenderTextureComponent, 3, Float2, float, dimensions, y)
DEFINE_SOA_TYPE(RenderTextureComponent, 4, GLuint, texId)

class RenderTextureComponentSystem: public ComponentSystem<RenderTextureComponent>
{
public:
	RenderTextureComponentSystem() = default;

	void OnInitialize(EventManager* eventManager, const RenderTextureComponent::Aos& component, size_t entity) override;
	void OnPostInitialize(std::multimap<size_t, Event*>::_Pairii events, RenderTextureComponent::Soa* component, size_t entity) override;
	void OnUpdate(EventManager* eventManager, const RenderTextureComponent::Aos& component, size_t entity) override;
	void OnLateUpdate(std::multimap<size_t, Event*>::_Pairii events, RenderTextureComponent::Soa* component, size_t entity) override;
	void OnCleanUp(RenderTextureComponent::Soa* component) override;
	void OnDraw(RenderQueue* renderQueue, const RenderTextureComponent::Aos& component, TransformComponent::Aos transform) override;

private:
};