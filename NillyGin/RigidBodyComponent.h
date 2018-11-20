#pragma once
#include "Structs.h"
#include "ComponentSystem.h"

struct RigidBodyComponent
{
	struct Aos
	{
		bool isStatic;
	};
	struct Soa
	{
		bool *isStatic;
	};
};

DEFINE_SOA_CLASS(RigidBodyComponent, 1, 0)
DEFINE_SOA_TYPE(RigidBodyComponent, 0, bool, isStatic)

class RigidBodyComponentSystem : public ComponentSystem<RigidBodyComponent>
{
public:
	void OnInitialize(EventManager* eventManager, const RigidBodyComponent::Aos& component, size_t entity) override;
	void OnPostInitialize(std::multimap<size_t, Event*>::_Pairii events, RigidBodyComponent::Soa* component, size_t entity) override;
	void OnUpdate(EventManager* eventManager, const RigidBodyComponent::Aos& component, size_t entity) override;
	void OnLateUpdate(std::multimap<size_t, Event*>::_Pairii events, RigidBodyComponent::Soa* component, size_t entity) override;
	void OnDraw(RenderQueue* renderQueue, const RigidBodyComponent::Aos& component, TransformComponent::Aos transform) override;
	void OnCleanUp(RigidBodyComponent::Soa* component) override;
};