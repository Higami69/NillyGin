#include "pch.h"
#include "SystemManager.h"
#include "ComponentSystem.h"
#include <algorithm>

void SystemManager::AddSystem(ComponentSystemInterface* system)
{
	m_pSystems.push_back(system);
}

void SystemManager::RemoveSystem(ComponentSystemInterface* system)
{
	m_pSystems.erase(std::remove(m_pSystems.begin(), m_pSystems.end(), system));
}

void SystemManager::AddTransformSystem(ComponentSystemInterface* system)
{
	if(m_pTransformSystem == nullptr)
	{
		m_pTransformSystem = system;
		return;
	}

	//TODO: Throw/Log Error
}

void SystemManager::AddRenderSystem(ComponentSystemInterface* system)
{
	if(m_pRenderSystem == nullptr)
	{
		m_pRenderSystem = system;
		return;
	}

	//TODO: Throw/Log Error
}

void SystemManager::Update()
{
	//Update
	for(size_t i = 0; i < m_pSystems.size();i++)
	{
		m_Threads.push_back(std::thread(&ComponentSystemInterface::Update,m_pSystems[i]));
	}
	for (size_t i = 0; i < m_Threads.size(); i++)
	{
		m_Threads[i].join();
	}
	m_Threads.clear();

	//LateUpdate
	for (size_t i = 0; i < m_pSystems.size(); i++)
	{
		m_Threads.push_back(std::thread(&ComponentSystemInterface::LateUpdate, m_pSystems[i]));
	}
	for (size_t i = 0; i < m_Threads.size(); i++)
	{
		m_Threads[i].join();
	}
	m_Threads.clear();

	//Draw
}

void SystemManager::CleanUp()
{
	for (size_t i = 0; i < m_pSystems.size(); i++)
	{
		m_Threads.push_back(std::thread(&ComponentSystemInterface::CleanUp, m_pSystems[i]));
	}
	for(size_t i = 0; i < m_Threads.size(); i++)
	{
		m_Threads[i].join();
	}
	m_Threads.clear();
	m_pSystems.clear();
}
