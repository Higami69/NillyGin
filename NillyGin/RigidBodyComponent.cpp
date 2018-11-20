#include "pch.h"
#include "RigidBodyComponent.h"
#include "CommonInitializeEvents.h"

void RigidBodyComponentSystem::OnInitialize(EventManager* eventManager, const RigidBodyComponent::Aos& component, size_t entity)
{
	//If entity is static, notify all components that need to know
	if(component.isStatic)
	{
		eventManager->AddEvent("Static", entity, new SetStaticEvent());
	}
}

void RigidBodyComponentSystem::OnPostInitialize(std::multimap<size_t, Event*>::_Pairii events, RigidBodyComponent::Soa* component, size_t entity)
{
}

void RigidBodyComponentSystem::OnUpdate(EventManager* eventManager, const RigidBodyComponent::Aos& component, size_t entity)
{
}

void RigidBodyComponentSystem::OnLateUpdate(std::multimap<size_t, Event*>::_Pairii events, RigidBodyComponent::Soa* component, size_t entity)
{
}

void RigidBodyComponentSystem::OnDraw(RenderQueue* renderQueue, const RigidBodyComponent::Aos& component, TransformComponent::Aos transform)
{
}

void RigidBodyComponentSystem::OnCleanUp(RigidBodyComponent::Soa* component)
{
}
