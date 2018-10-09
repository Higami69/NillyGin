#pragma once
#include "Singleton.h"
#include <vector>
#include <thread>

class ComponentSystemInterface;

class SystemManager : public Singleton<SystemManager>
{
public:
	SystemManager() = default;

	void AddSystem(ComponentSystemInterface* system);
	void RemoveSystem(ComponentSystemInterface* system);
	void AddTransformSystem(ComponentSystemInterface* system);
	void AddRenderSystem(ComponentSystemInterface* system);

	void Update();
	void CleanUp();

private:
	ComponentSystemInterface* m_pTransformSystem = nullptr;
	ComponentSystemInterface* m_pRenderSystem = nullptr;
	std::vector<ComponentSystemInterface*> m_pSystems;
	std::vector<std::thread> m_Threads;
};