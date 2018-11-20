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
	TransformComponentSystem() = default;
	~TransformComponentSystem() = default;

	void OnInitialize(EventManager* eventManager, const TransformComponent::Aos& component, size_t entity) override;
	void OnPostInitialize(std::multimap < size_t, Event*>::_Pairii events, TransformComponent::Soa* component, size_t entity) override;
	void OnUpdate(EventManager* eventManager, const TransformComponent::Aos& component, size_t entity) override;
	void OnLateUpdate(std::multimap < size_t, Event*>::_Pairii events, TransformComponent::Soa* component, size_t entity) override;
	void OnCleanUp(TransformComponent::Soa* component) override;
	void OnDraw(RenderQueue* renderQueue, const TransformComponent::Aos& component, TransformComponent::Aos transform) override;

	TransformComponent::Aos GetTransform(size_t entity);
	TransformComponent::Aos GetTransformStatic(size_t entity);
private:
};
