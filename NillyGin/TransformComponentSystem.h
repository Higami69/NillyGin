#pragma once
#include "ComponentSystem.h"
#include "TransformComponent.h"
#include "EventManager.h"

//Events
enum class Direction
{
	UP, DOWN, LEFT, RIGHT
};
struct MoveEvent : public Event
{
	MoveEvent(Direction dir, float dist);

	Direction dir;
	float distance;
};

class TransformComponentSystem : public ComponentSystem<TransformComponent>
{
public:
	TransformComponentSystem();
	~TransformComponentSystem() = default;

	void OnUpdate(TransformComponent::Soa* component, size_t entity) override;
	void OnLateUpdate(TransformComponent::Soa* component, size_t entity) override;
	void OnCleanUp(TransformComponent::Soa* component) override;
	void OnDraw(const TransformComponent::Aos& component, TransformComponent::Aos transform) override;

	TransformComponent::Aos GetTransform(size_t entity);
private:
};
