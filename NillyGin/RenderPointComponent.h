#pragma once
#include "Structs.h"
#include "ComponentSystem.h"

struct RenderPointComponent
{
	struct Aos
	{
		Colour::Aos colour;
		float pointSize;
	};
	struct Soa
	{
		Colour::Soa *colour;
		float *pointSize;
	};
};

DEFINE_SOA_CLASS(RenderPointComponent, 5, 1)
DEFINE_SOA_STRUCT(RenderPointComponent,0,Colour::Soa, colour)
DEFINE_SOA_TYPE_STRUCT(RenderPointComponent, 0, Colour, float, colour, r)
DEFINE_SOA_TYPE_STRUCT(RenderPointComponent, 1, Colour, float, colour, g)
DEFINE_SOA_TYPE_STRUCT(RenderPointComponent, 2, Colour, float, colour, b)
DEFINE_SOA_TYPE_STRUCT(RenderPointComponent, 3, Colour, float, colour, a)
DEFINE_SOA_TYPE(RenderPointComponent,4,float,pointSize)

class RenderPointComponentSystem : public ComponentSystem<RenderPointComponent>
{
public:
	RenderPointComponentSystem();

	void OnInitialize(EventManager* eventManager, const RenderPointComponent::Aos& component, size_t entity) override;
	void OnPostInitialize(std::multimap<size_t, Event*>::_Pairii events, RenderPointComponent::Soa* component, size_t entity) override;
	void OnUpdate(EventManager* eventManager, const RenderPointComponent::Aos& component, size_t entity) override;
	void OnLateUpdate(std::multimap<size_t, Event*>::_Pairii events, RenderPointComponent::Soa* component, size_t entity) override;
	void OnCleanUp(RenderPointComponent::Soa* component) override;
	void OnDraw(RenderQueue* renderQueue, const RenderPointComponent::Aos& component, TransformComponent::Aos transform) override;

private:
};
