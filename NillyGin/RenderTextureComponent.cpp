#include "pch.h"
#include "RenderTextureComponent.h"
#include "RenderQueue.h"

void RenderTextureComponentSystem::OnInitialize(EventManager* eventManager, const RenderTextureComponent::Aos& component, size_t entity)
{
}

void RenderTextureComponentSystem::OnPostInitialize(std::multimap<size_t, Event*>::_Pairii events, RenderTextureComponent::Soa* component, size_t entity)
{
}

void RenderTextureComponentSystem::OnUpdate(EventManager* eventManager, const RenderTextureComponent::Aos& component, size_t entity)
{
}

void RenderTextureComponentSystem::OnLateUpdate(std::multimap<size_t, Event*>::_Pairii events, RenderTextureComponent::Soa* component, size_t entity)
{
}

void RenderTextureComponentSystem::OnCleanUp(RenderTextureComponent::Soa* component)
{
}

void RenderTextureComponentSystem::OnDraw(RenderQueue* renderQueue, const RenderTextureComponent::Aos& component, TransformComponent::Aos transform)
{
	RenderTextureTask::Aos task{};
	task.botLeft = Float2::Aos(transform.pos.x + component.offset.x - (component.dimensions.x / 2.f), transform.pos.y + component.offset.y - (component.dimensions.y / 2.f));
	task.dimensions = component.dimensions;
	task.depth = transform.pos.z;
	task.texId = component.texId;
	renderQueue->AddTask<RenderTextureTask>(task);
}