#pragma once
#include "Structs.h"
#include "ComponentSystem.h"

struct RenderTriangleComponent
{
	struct Aos
	{
		Float2::Aos point1, point2, point3;
		Colour::Aos colour;
		float lineWidth;
		bool isFilled;
	};
	struct Soa
	{
		Float2::Soa *point1, *point2, *point3;
		Colour::Soa *colour;
		float *lineWidth;
		bool *isFilled;
	};
};

DEFINE_SOA_CLASS(RenderTriangleComponent, 12, 4)
DEFINE_SOA_STRUCT(RenderTriangleComponent, 0, Float2::Soa, point1)
DEFINE_SOA_STRUCT(RenderTriangleComponent, 1, Float2::Soa, point2)
DEFINE_SOA_STRUCT(RenderTriangleComponent, 2, Float2::Soa, point3)
DEFINE_SOA_STRUCT(RenderTriangleComponent, 3, Colour::Soa, colour)
DEFINE_SOA_TYPE_STRUCT(RenderTriangleComponent, 0, Float2, float, point1, x)
DEFINE_SOA_TYPE_STRUCT(RenderTriangleComponent, 1, Float2, float, point1, y)
DEFINE_SOA_TYPE_STRUCT(RenderTriangleComponent, 2, Float2, float, point2, x)
DEFINE_SOA_TYPE_STRUCT(RenderTriangleComponent, 3, Float2, float, point2, y)
DEFINE_SOA_TYPE_STRUCT(RenderTriangleComponent, 4, Float2, float, point3, x)
DEFINE_SOA_TYPE_STRUCT(RenderTriangleComponent, 5, Float2, float, point3, y)
DEFINE_SOA_TYPE_STRUCT(RenderTriangleComponent, 6, Colour, float, colour, r)
DEFINE_SOA_TYPE_STRUCT(RenderTriangleComponent, 7, Colour, float, colour, g)
DEFINE_SOA_TYPE_STRUCT(RenderTriangleComponent, 8, Colour, float, colour, b)
DEFINE_SOA_TYPE_STRUCT(RenderTriangleComponent, 9, Colour, float, colour, a)
DEFINE_SOA_TYPE(RenderTriangleComponent, 10, float, lineWidth)
DEFINE_SOA_TYPE(RenderTriangleComponent, 11, bool, isFilled)

class RenderTriangleComponentSystem : public ComponentSystem<RenderTriangleComponent>
{
public:
	RenderTriangleComponentSystem();

	void OnInitialize(EventManager* eventManager, const RenderTriangleComponent::Aos& component, size_t entity) override;
	void OnPostInitialize(std::multimap<size_t, Event*>::_Pairii events, RenderTriangleComponent::Soa* component, size_t entity) override;
	void OnUpdate(EventManager* eventManager, const RenderTriangleComponent::Aos& component, size_t entity) override;
	void OnLateUpdate(std::multimap<size_t, Event*>::_Pairii events, RenderTriangleComponent::Soa* component, size_t entity) override;
	void OnCleanUp(RenderTriangleComponent::Soa* component) override;
	void OnDraw(RenderQueue* renderQueue, const RenderTriangleComponent::Aos& component, TransformComponent::Aos transform) override;

	RenderTriangleComponent::Aos CreateTriangleAroundPoint(float width, float height, Colour::Aos colour, bool isFilled = true, float lineWidth = 0);
private:
};