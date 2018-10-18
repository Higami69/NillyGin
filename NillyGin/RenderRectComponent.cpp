#include "pch.h"
#include "RenderRectComponent.h"

RenderRectComponentSystem::RenderRectComponentSystem()
{
}

RenderRectComponentSystem::~RenderRectComponentSystem()
{
}

void RenderRectComponentSystem::OnUpdate(RenderRectComponent::Soa* component, size_t entity)
{	
}

void RenderRectComponentSystem::OnLateUpdate(RenderRectComponent::Soa* component, size_t entity)
{
}

void RenderRectComponentSystem::OnCleanUp(RenderRectComponent::Soa* component)
{
}

void RenderRectComponentSystem::OnDraw(const RenderRectComponent::Aos& component, TransformComponent::Aos transform)
{
	auto renderer = Renderer::GetInstance();

	renderer->DrawRectangle(transform.xPos, transform.yPos, component.width, component.height,
		Colour(component.color_r, component.color_g, component.color_b, component.color_a));
}
