#include "pch.h"
#include "TransformComponent.h"

TransformComponentSystem::TransformComponentSystem()
{
	auto systemManager = SystemManager::GetInstance();
	ComponentSystemInterface* _this = this;
	systemManager->RemoveSystem(_this);
	systemManager->AddTransformSystem(_this);
}

void TransformComponentSystem::OnUpdate(TransformComponent::Soa* component, size_t entity)
{
}

void TransformComponentSystem::OnLateUpdate(TransformComponent::Soa* component, size_t entity)
{
}

void TransformComponentSystem::OnCleanUp(TransformComponent::Soa* component)
{
}
