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

DEFINE_SOA_CLASS(MovementComponent,1)
DEFINE_SOA_TYPE(MovementComponent,0,float,speed)

class MovementComponentSystem : public ComponentSystem<MovementComponent>
{
public:
	MovementComponentSystem();
	~MovementComponentSystem() = default;

	void OnUpdate(MovementComponent::Soa* component, size_t entity) override;
	void OnLateUpdate(MovementComponent::Soa* component, size_t entity) override;
	void OnCleanUp(MovementComponent::Soa* component) override;

private:
};