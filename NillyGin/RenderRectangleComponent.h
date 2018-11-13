#pragma once
#include "Structs.h"
#include "ComponentSystem.h"

struct RenderRectangleComponent
{
	struct Aos
	{
		Float2::Aos bottomLeft, dimensions;
		Colour::Aos colour;
		float lineWidth;
		bool isFilled;
	};
	struct Soa
	{
		Float2::Soa *bottomLeft, *dimensions;
		Colour::Soa *colour;
		float *lineWidth;
		bool *isFilled;
	};
};

DEFINE_SOA_CLASS(RenderRectangleComponent, 10 ,3)
DEFINE_SOA_STRUCT(RenderRectangleComponent, 0, Float2::Soa, bottomLeft)
DEFINE_SOA_STRUCT(RenderRectangleComponent, 1, Float2::Soa, dimensions)
DEFINE_SOA_STRUCT(RenderRectangleComponent, 2, Colour::Soa, colour)
DEFINE_SOA_TYPE_STRUCT(RenderRectangleComponent, 0, Float2, float, bottomLeft, x)
DEFINE_SOA_TYPE_STRUCT(RenderRectangleComponent, 1, Float2, float, bottomLeft, y)
DEFINE_SOA_TYPE_STRUCT(RenderRectangleComponent, 2, Float2, float, dimensions, x)
DEFINE_SOA_TYPE_STRUCT(RenderRectangleComponent, 3, Float2, float, dimensions, y)
DEFINE_SOA_TYPE_STRUCT(RenderRectangleComponent, 4, Colour, float, colour, r)
DEFINE_SOA_TYPE_STRUCT(RenderRectangleComponent, 5, Colour, float, colour, g)
DEFINE_SOA_TYPE_STRUCT(RenderRectangleComponent, 6, Colour, float, colour, b)
DEFINE_SOA_TYPE_STRUCT(RenderRectangleComponent, 7, Colour, float, colour, a)
DEFINE_SOA_TYPE(RenderRectangleComponent, 8, float, lineWidth)
DEFINE_SOA_TYPE(RenderRectangleComponent, 9, bool, isFilled)

class RenderRectangleComponentSystem : public ComponentSystem<RenderRectangleComponent>
{
public:
	RenderRectangleComponentSystem();

	void OnUpdate(RenderRectangleComponent::Soa* component, size_t entity) override;
	void OnLateUpdate(RenderRectangleComponent::Soa* component, size_t entity) override;
	void OnCleanUp(RenderRectangleComponent::Soa* component) override;
	void OnDraw(RenderQueue* renderQueue, const RenderRectangleComponent::Aos& component, TransformComponent::Aos transform) override;
private:
};