#pragma once
#include "ComponentSystem.h"
#include "Renderer.h"

struct RenderRectComponent
{
	struct Aos
	{
		float width, height, color_r, color_g, color_b, color_a;
	};
	struct Soa
	{
		float *width, *height, *color_r, *color_g, *color_b, *color_a;
	};
};

DEFINE_SOA_CLASS(RenderRectComponent,6)
DEFINE_SOA_TYPE(RenderRectComponent, 0, float, width)
DEFINE_SOA_TYPE(RenderRectComponent, 1, float, height)
DEFINE_SOA_TYPE(RenderRectComponent, 2, float, color_r)
DEFINE_SOA_TYPE(RenderRectComponent, 3, float, color_g)
DEFINE_SOA_TYPE(RenderRectComponent, 4, float, color_b)
DEFINE_SOA_TYPE(RenderRectComponent, 5, float, color_a)


class RenderRectComponentSystem : public ComponentSystem<RenderRectComponent>
{
public:
	RenderRectComponentSystem();
	~RenderRectComponentSystem();

	void OnUpdate(RenderRectComponent::Soa* component, size_t entity) override;
	void OnLateUpdate(RenderRectComponent::Soa* component, size_t entity) override;
	void OnCleanUp(RenderRectComponent::Soa* component) override;
};