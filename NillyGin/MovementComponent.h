#pragma once
#include "ComponentSystem.h"

struct MovementComponent
{
	struct Aos
	{
		float speed;
	};
	struct Soa
	{
		float *speed;
	};
};

DEFINE_SOA_CLASS(MovementComponent,1, 0)
DEFINE_SOA_TYPE(MovementComponent,0,float,speed)

class MovementComponentSystem : public ComponentSystem<MovementComponent>
{
public:
	MovementComponentSystem();
	~MovementComponentSystem() = default;

	void OnInitialize(EventManager* eventManager, const MovementComponent::Aos& component, size_t entity) override;
	void OnPostInitialize(std::multimap<size_t, Event*>::_Pairii events, MovementComponent::Soa* component, size_t entity) override;
	void OnUpdate(EventManager* eventManager, const MovementComponent::Aos& component, size_t entity) override;
	void OnLateUpdate(std::multimap<size_t, Event*>::_Pairii events, MovementComponent::Soa* component, size_t entity) override;
	void OnCleanUp(MovementComponent::Soa* component) override;
	void OnDraw(RenderQueue* renderQueue, const MovementComponent::Aos& component, TransformComponent::Aos transform) override;

private:
};