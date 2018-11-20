#include "pch.h"
#include "RenderLineComponent.h"
#include "RenderQueue.h"

RenderLineComponentSystem::RenderLineComponentSystem()
{
}

void RenderLineComponentSystem::OnInitialize(EventManager* eventManager, const RenderLineComponent::Aos& component,
	size_t entity)
{
}

void RenderLineComponentSystem::OnPostInitialize(std::multimap<size_t, Event*>::_Pairii events,
	RenderLineComponent::Soa* component, size_t entity)
{
}

void RenderLineComponentSystem::OnUpdate(EventManager* eventManager, const RenderLineComponent::Aos& component, size_t entity)
{
}

void RenderLineComponentSystem::OnLateUpdate(std::multimap<size_t, Event*>::_Pairii events, RenderLineComponent::Soa* component, size_t entity)
{
}

void RenderLineComponentSystem::OnCleanUp(RenderLineComponent::Soa* component)
{
}

void RenderLineComponentSystem::OnDraw(RenderQueue* renderQueue, const RenderLineComponent::Aos& component,
	TransformComponent::Aos transform)
{
	RenderLineTask::Aos task;
	task.point1 = Float2::Aos(transform.pos.x + component.point1.x, transform.pos.y + component.point1.y);
	task.point2 = Float2::Aos(transform.pos.x + component.point2.x, transform.pos.y + component.point2.y);
	task.colour = component.colour;
	task.lineWidth = component.lineWidth;
	task.depth = transform.pos.z;
	renderQueue->AddTask<RenderLineTask>(task);
}
