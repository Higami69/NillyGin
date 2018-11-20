#include "pch.h"
#include "RenderPointComponent.h"
#include "RenderQueue.h"

RenderPointComponentSystem::RenderPointComponentSystem()
{
}

void RenderPointComponentSystem::OnInitialize(EventManager* eventManager, const RenderPointComponent::Aos& component, size_t entity)
{
}

void RenderPointComponentSystem::OnPostInitialize(std::multimap<size_t, Event*>::_Pairii events, RenderPointComponent::Soa* component, size_t entity)
{
}

void RenderPointComponentSystem::OnUpdate(EventManager* eventManager, const RenderPointComponent::Aos& component, size_t entity)
{
}

void RenderPointComponentSystem::OnLateUpdate(std::multimap<size_t, Event*>::_Pairii events, RenderPointComponent::Soa* component, size_t entity)
{
}

void RenderPointComponentSystem::OnCleanUp(RenderPointComponent::Soa* component)
{
}

void RenderPointComponentSystem::OnDraw(RenderQueue* renderQueue, const RenderPointComponent::Aos& component, TransformComponent::Aos transform)
{
	RenderPointTask::Aos task;
	task.point = transform.pos;
	task.colour = component.colour;
	task.pointSize = component.pointSize;
	renderQueue->AddTask<RenderPointTask>(task);
}
