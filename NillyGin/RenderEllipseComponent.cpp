#include "pch.h"
#include "RenderEllipseComponent.h"
#include "RenderQueue.h"

RenderEllipseComponentSystem::RenderEllipseComponentSystem()
{
}

void RenderEllipseComponentSystem::OnUpdate(RenderEllipseComponent::Soa* component, size_t entity)
{
}

void RenderEllipseComponentSystem::OnLateUpdate(RenderEllipseComponent::Soa* component, size_t entity)
{
}

void RenderEllipseComponentSystem::OnCleanUp(RenderEllipseComponent::Soa* component)
{
}

void RenderEllipseComponentSystem::OnDraw(RenderQueue* renderQueue, const RenderEllipseComponent::Aos& component, TransformComponent::Aos transform)
{
	if (component.isFilled)
	{
		RenderFilledEllipseTask::Aos task;
		task.center = Float2::Aos(transform.pos.x, transform.pos.y);
		task.colour = component.colour;
		task.depth = transform.pos.z;
		task.dimensions = component.dimensions;
		task.nrSections = component.nrSections;
		renderQueue->AddTask<RenderFilledEllipseTask>(task);
	}
	else
	{
		RenderEllipseTask::Aos task;
		task.center = Float2::Aos(transform.pos.x, transform.pos.y);
		task.colour = component.colour;
		task.depth = transform.pos.z;
		task.dimensions = component.dimensions;
		task.nrSections = component.nrSections;
		task.lineWidth = component.lineWidth;
		renderQueue->AddTask<RenderEllipseTask>(task);
	}
}
