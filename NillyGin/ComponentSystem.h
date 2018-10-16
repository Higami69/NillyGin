#pragma once
#include "Singleton.h"
#include "DataBlockSoa.h"
#include <vector>
#include <thread>
#include <map>
#include "SystemManager.h"
#include "EntityManager.h"
#include <algorithm>

class ComponentSystemInterface
{
public:
	virtual ~ComponentSystemInterface()
	{
	}

	virtual void Update() = 0;
	virtual void LateUpdate() = 0;
	virtual void CleanUp() = 0;

	virtual size_t GetComponentIndex(size_t entity) = 0;
};

template<typename T>
class ComponentSystem : public ComponentSystemInterface
{
public:
	ComponentSystem();
	virtual ~ComponentSystem();

	void AddComponent(size_t entity, const typename T::Aos& component);

	void Update() override;
	void LateUpdate() override;
	void CleanUp() override;

	size_t GetComponentIndex(size_t entity) override;

	virtual void OnUpdate(typename T::Soa* component, size_t entity) = 0;
	virtual void OnLateUpdate(typename T::Soa* component, size_t entity) = 0;
	virtual void OnCleanUp(typename T::Soa* component) = 0;

protected:
	DataBlockSoa<T> m_Components;

private:
	void CollectGarbage();

private:
	std::vector<size_t> m_CompsToDelete, m_ValidComps;

	std::map<size_t,size_t> m_EntityComponentLinks; //left = ComponentId, right = EntityId
};

template <typename T>
ComponentSystem<T>::ComponentSystem()
{
	SystemManager::GetInstance()->AddSystem(this);
}

template <typename T>
ComponentSystem<T>::~ComponentSystem()
{
}

template <typename T>
void ComponentSystem<T>::AddComponent(size_t entity, const typename T::Aos& component)
{
	size_t compIdx = m_Components.Add(component);
	m_EntityComponentLinks[compIdx] = entity;
}

template <typename T>
void ComponentSystem<T>::Update()
{
	if (m_Components.GetSize() > 0)
	{
		auto entityManager = EntityManager::GetInstance();
		for(size_t i = 0; i < m_Components.GetSize();++i)
		{
			if(entityManager->IsAlive(m_EntityComponentLinks[i]))
			{
				m_ValidComps.push_back(i);
				continue;
			}

			m_CompsToDelete.push_back(i);
		}

		for(size_t i : m_ValidComps)
		{
			OnUpdate(&m_Components.GetSoa(i), m_EntityComponentLinks[i]);
		}
	}
}

template <typename T>
void ComponentSystem<T>::LateUpdate()
{
	if (m_Components.GetSize() > 0)
	{
		auto entityManager = EntityManager::GetInstance();

		for (size_t i : m_ValidComps)
		{
			OnLateUpdate(&m_Components.GetSoa(i), m_EntityComponentLinks[i]);
		}

		m_ValidComps.clear();
		CollectGarbage();
	}
}

template <typename T>
void ComponentSystem<T>::CleanUp()
{
	auto entityManager = EntityManager::GetInstance();

	for (size_t i = 0; i < m_Components.GetSize(); ++i)
	{
		OnCleanUp(&m_Components.GetSoa(i));
	}
}

template <typename T>
size_t ComponentSystem<T>::GetComponentIndex(size_t entity)
{
	return std::find_if(m_EntityComponentLinks.begin(), m_EntityComponentLinks.end(), [entity](const auto& link) {return entity == link.second; })->second;
}

//template <typename T>
//void ComponentSystem<T>::MarkGarbage()
//{
//	size_t aliveInRow = 0;
//	auto entityManager = EntityManager::GetInstance();
//	auto links = m_EntityComponentLinks;
//
//		while (!links.empty() && aliveInRow < 4)
//		{
//			size_t idx = rand() % links.size();
//			auto it = links.begin();
//			std::advance(it, idx);
//
//			if (entityManager->IsAlive((*it).second))
//			{
//				++aliveInRow;
//				continue;
//			}
//
//			aliveInRow = 0;
//			m_CompsToDelete.push_back((*it).first);
//			links.erase(it);
//		}
//}

template <typename T>
void ComponentSystem<T>::CollectGarbage()
{
	for(size_t i : m_CompsToDelete)
	{
		size_t last = m_Components.Remove(i);
		m_EntityComponentLinks[i] = m_EntityComponentLinks[last];
		m_EntityComponentLinks.erase(m_EntityComponentLinks.find(last));
	}
	m_CompsToDelete.clear();
}
