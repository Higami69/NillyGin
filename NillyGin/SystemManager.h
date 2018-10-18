#pragma once
#include <vector>
#include <thread>
#include "TransformComponent.h"


class ComponentSystemInterface;

class SystemManager
{
public:
	SystemManager() = default;

	void AddSystem(ComponentSystemInterface* system);
	void RemoveSystem(ComponentSystemInterface* system);
	void AddTransformSystem(ComponentSystemInterface* system);
	void AddRenderSystem(ComponentSystemInterface* system);

	void Update();
	void CleanUp();

	TransformComponent::Aos GetTransform(size_t entity);

private:
	ComponentSystemInterface* m_pTransformSystem = nullptr;
	std::vector<ComponentSystemInterface*> m_pRenderSystems;
	std::vector<ComponentSystemInterface*> m_pSystems;
	std::vector<std::thread> m_Threads;
};