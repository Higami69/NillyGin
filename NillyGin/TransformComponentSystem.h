#pragma once
#include "ComponentSystem.h"
#include "TransformComponent.h"

#pragma region EventFlags
#define MOVE_UP 0x0001u		//To move down pass negative value
#define MOVE_RIGHT 0x0002u	//To move left pass negative value
#pragma endregion 


class TransformComponentSystem : public ComponentSystem<TransformComponent>
{
public:
	TransformComponentSystem();

	void OnUpdate(TransformComponent::Soa* component, size_t entity) override;
	void OnLateUpdate(TransformComponent::Soa* component, size_t entity) override;
	void OnCleanUp(TransformComponent::Soa* component) override;

	TransformComponent::Aos GetTransform(size_t entity);
private:
};
