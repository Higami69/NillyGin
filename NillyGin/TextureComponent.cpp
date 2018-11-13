#include "pch.h"
#include "TextureComponent.h"
#include "Renderer.h"

TextureComponentSystem::TextureComponentSystem()
{
}

void TextureComponentSystem::OnUpdate(TextureComponent::Soa* component, size_t entity)
{
}

void TextureComponentSystem::OnLateUpdate(TextureComponent::Soa* component, size_t entity)
{
}

void TextureComponentSystem::OnCleanUp(TextureComponent::Soa* component)
{
}

void TextureComponentSystem::OnDraw(RenderQueue* renderQueue, const TextureComponent::Aos& component, TransformComponent::Aos transform)
{
}
