#include "pch.h"
#include "RenderRectangleComponent.h"
#include "RenderQueue.h"

RenderRectangleComponentSystem::RenderRectangleComponentSystem()
{
}

void RenderRectangleComponentSystem::OnInitialize(EventManager* eventManager, const RenderRectangleComponent::Aos& component, size_t entity)
{
}

void RenderRectangleComponentSystem::OnPostInitialize(std::multimap<size_t, Event*>::_Pairii events, RenderRectangleComponent::Soa* component, size_t entity)
{
}

void RenderRectangleComponentSystem::OnUpdate(EventManager* eventManager, const RenderRectangleComponent::Aos& component, size_t entity)
{
}

void RenderRectangleComponentSystem::OnLateUpdate(std::multimap<size_t, Event*>::_Pairii events, RenderRectangleComponent::Soa* component, size_t entity)
{
}

void RenderRectangleComponentSystem::OnCleanUp(RenderRectangleComponent::Soa* component)
{
}

void RenderRectangleComponentSystem::OnDraw(RenderQueue* renderQueue, const RenderRectangleComponent::Aos& component, TransformComponent::Aos transform)
{
	if(component.isFilled)
	{
		RenderFilledRectangleTask::Aos task;
		task.depth = transform.pos.z;
		task.colour = component.colour;
		task.bottomLeft = Float2::Aos(transform.pos.x + component.bottomLeft.x, transform.pos.y + component.bottomLeft.y);
		task.dimensions = component.dimensions;
		renderQueue->AddTask<RenderFilledRectangleTask>(task);
	}
	else
	{
		RenderRectangleTask::Aos task;
		task.depth = transform.pos.z;
		task.lineWidth = component.lineWidth;
		task.colour = component.colour;
		task.bottomLeft = Float2::Aos(transform.pos.x + component.bottomLeft.x, transform.pos.y + component.bottomLeft.y);
		task.dimensions = component.dimensions;
		renderQueue->AddTask<RenderRectangleTask>(task);
	}
}
