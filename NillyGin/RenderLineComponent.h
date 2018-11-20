#pragma once
#include "Structs.h"
#include "ComponentSystem.h"

struct RenderLineComponent
{
	struct Aos
	{
		Float2::Aos point1, point2;
		Colour::Aos colour;
		float lineWidth;
	};
	struct Soa
	{
		Float2::Soa *point1, *point2;
		Colour::Soa *colour;
		float *lineWidth;
	};
};

DEFINE_SOA_CLASS(RenderLineComponent, 9, 3)
DEFINE_SOA_STRUCT(RenderLineComponent, 0, Float2::Soa, point1)
DEFINE_SOA_STRUCT(RenderLineComponent, 1, Float2::Soa, point2)
DEFINE_SOA_STRUCT(RenderLineComponent, 2, Colour::Soa, colour)
DEFINE_SOA_TYPE_STRUCT(RenderLineComponent, 0, Float2, float, point1, x)
DEFINE_SOA_TYPE_STRUCT(RenderLineComponent, 1, Float2, float, point1, y)
DEFINE_SOA_TYPE_STRUCT(RenderLineComponent, 2, Float2, float, point2, x)
DEFINE_SOA_TYPE_STRUCT(RenderLineComponent, 3, Float2, float, point2, y)
DEFINE_SOA_TYPE_STRUCT(RenderLineComponent, 4, Colour, float, colour, r)
DEFINE_SOA_TYPE_STRUCT(RenderLineComponent, 5, Colour, float, colour, g)
DEFINE_SOA_TYPE_STRUCT(RenderLineComponent, 6, Colour, float, colour, b)
DEFINE_SOA_TYPE_STRUCT(RenderLineComponent, 7, Colour, float, colour, a)
DEFINE_SOA_TYPE(RenderLineComponent, 8, float, lineWidth)

class RenderLineComponentSystem : public ComponentSystem<RenderLineComponent>
{
public:
	RenderLineComponentSystem();

	void OnInitialize(EventManager* eventManager, const RenderLineComponent::Aos& component, size_t entity) override;
	void OnPostInitialize(std::multimap<size_t, Event*>::_Pairii events, RenderLineComponent::Soa* component, size_t entity) override;
	void OnUpdate(EventManager* eventManager, const RenderLineComponent::Aos& component, size_t entity) override;
	void OnLateUpdate(std::multimap<size_t, Event*>::_Pairii events, RenderLineComponent::Soa* component, size_t entity) override;
	void OnCleanUp(RenderLineComponent::Soa* component) override;
	void OnDraw(RenderQueue* renderQueue, const RenderLineComponent::Aos& component, TransformComponent::Aos transform) override;

private:
};