#include "pch.h"
#include "TransformComponentSystem.h"

MoveEvent::MoveEvent(Direction dir, float dist)
	:Event(0), dir(dir), distance(dist)
{
}

TransformComponentSystem::TransformComponentSystem()
{
	auto systemManager = SystemManager::GetInstance();
	ComponentSystemInterface* _this = this;
	systemManager->RemoveSystem(_this);
	systemManager->AddTransformSystem(_this);

	EventManager::GetInstance()->AddQueue("Transform");
}

void TransformComponentSystem::OnUpdate(TransformComponent::Soa* component, size_t entity)
{
}

void TransformComponentSystem::OnLateUpdate(TransformComponent::Soa* component, size_t entity)
{
	auto eventSystem = EventManager::GetInstance();
	auto queue = eventSystem->GetEventQueue("Transform");
	auto range = queue.equal_range(entity);

	auto it = range.first;
	do
	{
		if (it == queue.end()) return;

		switch(it->second->id)
		{
		case 0: //MoveEvent
			{
			auto event = (MoveEvent*)it->second;
				switch(event->dir)
				{
				case Direction::DOWN:
					*component->yPos -= event->distance;
					break;
				case Direction::LEFT:
					*component->xPos -= event->distance;
					break;
				case Direction::RIGHT:
					*component->xPos += event->distance;
					break;
				case Direction::UP:
					*component->yPos += event->distance;
					break;
				}
			break;
			}
		}
	} while (it++ != range.second);
}

void TransformComponentSystem::OnCleanUp(TransformComponent::Soa* component)
{
}

TransformComponent::Aos TransformComponentSystem::GetTransform(size_t entity)
{
	return m_Components.GetAos(GetComponentIndex(entity));
}
