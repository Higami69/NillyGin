#pragma once
#include "ComponentSystem.h"
#include "EntityManager.h"

#pragma region EventFlags
#define MOVE_UP 0x0001u		//To move down pass negative value
#define MOVE_RIGHT 0x0002u	//To move left pass negative value
#pragma endregion 

struct TransformComponent
{
	struct Aos
	{
		float xPos, yPos;
	};

	struct Soa
	{
		float *xPos, *yPos;
	};
};

DEFINE_SOA_CLASS(TransformComponent,2)
DEFINE_SOA_TYPE(TransformComponent,0,float,xPos)
DEFINE_SOA_TYPE(TransformComponent,1,float,yPos)

class TransformComponentSystem : public ComponentSystem<TransformComponent>
{
public:
	TransformComponentSystem();

	void OnUpdate(TransformComponent::Soa* component, size_t entity) override;
	void OnLateUpdate(TransformComponent::Soa* component, size_t entity) override;
	void OnCleanUp(TransformComponent::Soa* component) override;

private:
};