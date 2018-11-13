#include "pch.h"
#include "RenderPointComponent.h"
#include "RenderQueue.h"

RenderPointComponentSystem::RenderPointComponentSystem()
{
}

void RenderPointComponentSystem::OnUpdate(RenderPointComponent::Soa* component, size_t entity)
{
}

void RenderPointComponentSystem::OnLateUpdate(RenderPointComponent::Soa* component, size_t entity)
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
