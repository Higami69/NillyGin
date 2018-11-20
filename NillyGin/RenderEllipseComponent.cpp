#include "pch.h"
#include "RenderEllipseComponent.h"
#include "RenderQueue.h"

RenderEllipseComponentSystem::RenderEllipseComponentSystem()
{
}

void RenderEllipseComponentSystem::OnInitialize(EventManager* eventManager, const RenderEllipseComponent::Aos& component, size_t entity)
{
}

void RenderEllipseComponentSystem::OnPostInitialize(std::multimap<size_t, Event*>::_Pairii events, RenderEllipseComponent::Soa* component, size_t entity)
{
}

void RenderEllipseComponentSystem::OnUpdate(EventManager* eventManager, const RenderEllipseComponent::Aos& component, size_t entity)
{
}

void RenderEllipseComponentSystem::OnLateUpdate(std::multimap<size_t, Event*>::_Pairii events, RenderEllipseComponent::Soa* component, size_t entity)
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
