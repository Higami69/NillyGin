#include "pch.h"
#include "TextureComponent.h"
#include "Renderer.h"

TextureComponentSystem::TextureComponentSystem()
{
	ComponentSystemInterface* _This = this;
	auto systemManager = SystemManager::GetInstance();
	systemManager->RemoveSystem(_This);
	systemManager->AddRenderSystem(_This);
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

void TextureComponentSystem::OnDraw(const TextureComponent::Aos& component, TransformComponent::Aos transform)
{
	Renderer::GetInstance()->DrawTexture(component.texture, Float2(transform.xPos, transform.yPos), component.width, component.height);
}
