#include "pch.h"
#include "SystemManager.h"
#include "ComponentSystem.h"
#include "TransformComponent.h"
#include <algorithm>
#include "TransformComponentSystem.h"

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
	m_pRenderSystems.push_back(system);
}

void SystemManager::Update()
{
	//Update
	auto thread = std::thread(&ComponentSystemInterface::Update, m_pTransformSystem);
	for(size_t i = 0; i < m_pSystems.size();i++)
	{
		m_Threads.push_back(std::thread(&ComponentSystemInterface::Update,m_pSystems[i]));
	}
	for (size_t i = 0; i < m_Threads.size(); i++)
	{
		m_Threads[i].join();
	}
	thread.join();
	m_Threads.clear();

	//LateUpdate
	thread = std::thread(&ComponentSystemInterface::LateUpdate, m_pTransformSystem);
	for (size_t i = 0; i < m_pSystems.size(); i++)
	{
		m_Threads.push_back(std::thread(&ComponentSystemInterface::LateUpdate, m_pSystems[i]));
	}
	for (size_t i = 0; i < m_Threads.size(); i++)
	{
		m_Threads[i].join();
	}
	thread.join();
	m_Threads.clear();

	//Draw
	for (size_t i =0;i < m_pRenderSystems.size(); i++)
	{
		m_pRenderSystems[i]->Draw();
	}
}

void SystemManager::CleanUp()
{
	for (size_t i = 0; i < m_pSystems.size(); i++)
	{
		m_Threads.push_back(std::thread(&ComponentSystemInterface::CleanUp, m_pSystems[i]));
	}
	for(size_t i = 0; i < m_pSystems.size(); i++)
	{
		m_Threads[i].join();
		delete m_pSystems[i];
	}
	m_Threads.clear();
	m_pSystems.clear();

	for(size_t i = 0; i < m_pRenderSystems.size();i++)
	{
		m_Threads.push_back(std::thread(&ComponentSystemInterface::CleanUp, m_pRenderSystems[i]));
	}
	for(size_t i = 0; i < m_pRenderSystems.size();i++)
	{
		m_Threads[i].join();
		delete m_pRenderSystems[i];
	}
	m_Threads.clear();
	m_pRenderSystems.clear();

	m_pTransformSystem->CleanUp();
	delete m_pTransformSystem;
}

TransformComponent::Aos SystemManager::GetTransform(size_t entity)
{
	return ((TransformComponentSystem*)m_pTransformSystem)->GetTransform(entity);
}
