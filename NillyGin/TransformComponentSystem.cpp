#include "pch.h"
#include "TransformComponentSystem.h"

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

TransformComponent::Aos TransformComponentSystem::GetTransform(size_t entity)
{
	return m_Components.GetAos(GetComponentIndex(entity));
}
