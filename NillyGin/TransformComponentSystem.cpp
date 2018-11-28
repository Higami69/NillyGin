#include "pch.h"
#include "TransformComponentSystem.h"

MoveEvent::MoveEvent(Direction dir, float dist)
	:Event(0), dir(dir), distance(dist)
{
}

void TransformComponentSystem::OnInitialize(EventManager* eventManager, const TransformComponent::Aos& component, size_t entity)
{
}

void TransformComponentSystem::OnPostInitialize(std::multimap < size_t, Event*>::_Pairii events, TransformComponent::Soa* component, size_t entity)
{
}

void TransformComponentSystem::OnUpdate(EventManager* eventManager, const TransformComponent::Aos& component, size_t entity)
{
}

void TransformComponentSystem::OnLateUpdate(std::multimap < size_t, Event*>::_Pairii events, TransformComponent::Soa* component, size_t entity)
{

	auto it = events.first;
	do
	{
		switch(it->second->id)
		{
		case 0: //MoveEvent
			{
			auto event = (MoveEvent*)it->second;
				switch(event->dir)
				{
				case Direction::DOWN:
					*component->pos->y -= event->distance;
					break;
				case Direction::LEFT:
					*component->pos->x -= event->distance;
					break;
				case Direction::RIGHT:
					*component->pos->x += event->distance;
					break;
				case Direction::UP:
					*component->pos->y += event->distance;
					break;
				}
			break;
			}
		}
	} while (++it != events.second);
}

void TransformComponentSystem::OnCleanUp(TransformComponent::Soa* component)
{
}

void TransformComponentSystem::OnDraw(RenderQueue* renderQueue, const TransformComponent::Aos& component, TransformComponent::Aos transform)
{
}

TransformComponent::Aos TransformComponentSystem::GetTransform(size_t entity)
{
	return m_Components.GetAos(GetComponentIndex(entity));
}

TransformComponent::Aos TransformComponentSystem::GetTransformStatic(size_t entity)
{
	return m_StaticComponents.GetAos(GetComponentIndexStatic(entity));
}
