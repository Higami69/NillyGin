#pragma once
#include "Structs.h"
#include "ComponentSystem.h"

struct RenderEllipseComponent
{
	struct Aos
	{
		Float2::Aos dimensions;
		Colour::Aos colour;
		float lineWidth, nrSections;
		bool isFilled;
	};
	struct Soa
	{
		Float2::Soa *dimensions;
		Colour::Soa *colour;
		float *lineWidth, *nrSections;
		bool *isFilled;
	};
};

DEFINE_SOA_CLASS(RenderEllipseComponent, 9, 2)
DEFINE_SOA_STRUCT(RenderEllipseComponent, 0, Float2::Soa, dimensions)
DEFINE_SOA_STRUCT(RenderEllipseComponent, 1, Colour::Soa, colour)
DEFINE_SOA_TYPE_STRUCT(RenderEllipseComponent, 0, Float2, float, dimensions, x)
DEFINE_SOA_TYPE_STRUCT(RenderEllipseComponent, 1, Float2, float, dimensions, y)
DEFINE_SOA_TYPE_STRUCT(RenderEllipseComponent, 2, Colour, float, colour, r)
DEFINE_SOA_TYPE_STRUCT(RenderEllipseComponent, 3, Colour, float, colour, g)
DEFINE_SOA_TYPE_STRUCT(RenderEllipseComponent, 4, Colour, float, colour, b)
DEFINE_SOA_TYPE_STRUCT(RenderEllipseComponent, 5, Colour, float, colour, a)
DEFINE_SOA_TYPE(RenderEllipseComponent, 6, float, lineWidth)
DEFINE_SOA_TYPE(RenderEllipseComponent, 7, float, nrSections)
DEFINE_SOA_TYPE(RenderEllipseComponent, 8, bool, isFilled)

class RenderEllipseComponentSystem : public ComponentSystem<RenderEllipseComponent>
{
public:
	RenderEllipseComponentSystem();

	void OnInitialize(EventManager* eventManager, const RenderEllipseComponent::Aos& component, size_t entity) override;
	void OnPostInitialize(std::multimap<size_t, Event*>::_Pairii events, RenderEllipseComponent::Soa* component, size_t entity) override;
	void OnUpdate(EventManager* eventManager, const RenderEllipseComponent::Aos& component, size_t entity) override;
	void OnLateUpdate(std::multimap<size_t, Event*>::_Pairii events, RenderEllipseComponent::Soa* component, size_t entity) override;
	void OnCleanUp(RenderEllipseComponent::Soa* component) override;
	void OnDraw(RenderQueue* renderQueue, const RenderEllipseComponent::Aos& component, TransformComponent::Aos transform) override;

private:
};