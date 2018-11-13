#pragma once
#include "Singleton.h"
#include "DataBlockSoa.h"
#include <vector>
#include <thread>
#include <map>
#include "SystemManager.h"
#include "EntityManager.h"
#include <algorithm>

#define RENDER_SYSTEM 0x0001u
#define TRANSFORM_SYSTEM 0x0002u

class RenderQueue;

class ComponentSystemInterface
{
public:
	virtual ~ComponentSystemInterface() = default;

	virtual void Update() = 0;
	virtual void LateUpdate() = 0;
	virtual void CleanUp() = 0;
	virtual void Draw() = 0;

	virtual size_t GetComponentIndex(size_t entity) = 0;
};

template<typename T>
class ComponentSystem : public ComponentSystemInterface
{
public:
	ComponentSystem();
	virtual ~ComponentSystem();

	void Initialize(EntityManager* entityManager,SystemManager* systemManager, size_t flags = 0u);
	void SetRenderQueue(RenderQueue* renderQueue);

	void AddComponent(size_t entity, const typename T::Aos& component);

	void Update() override;
	void LateUpdate() override;
	void CleanUp() override;
	void Draw() override;

	size_t GetComponentIndex(size_t entity) override;

	virtual void OnUpdate(typename T::Soa* component, size_t entity) = 0;
	virtual void OnLateUpdate(typename T::Soa* component, size_t entity) = 0;
	virtual void OnCleanUp(typename T::Soa* component) = 0;
	virtual void OnDraw(RenderQueue* renderQueue, const typename T::Aos& component, TransformComponent::Aos transform) = 0;

protected:
	DataBlockSoa<T> m_Components;

private:
	void CollectGarbage();

private:
	std::vector<size_t> m_CompsToDelete, m_ValidComps;
	std::map<size_t,size_t> m_EntityComponentLinks; //left = ComponentId, right = EntityId

	EntityManager* m_pEntityManager;
	SystemManager* m_pSystemManager;
	RenderQueue* m_pRenderQueue = nullptr;
};

template <typename T>
ComponentSystem<T>::ComponentSystem()
	:m_pSystemManager(nullptr)
	,m_pEntityManager(nullptr)
{
}

template <typename T>
ComponentSystem<T>::~ComponentSystem()
{
}

template <typename T>
void ComponentSystem<T>::Initialize(EntityManager* entityManager, SystemManager* systemManager,size_t flags)
{
	m_pEntityManager = entityManager;
	m_pSystemManager = systemManager;
	
	switch(flags)
	{
	case 0u:
		m_pSystemManager->AddSystem(this);
		break;
	case RENDER_SYSTEM:
		m_pSystemManager->AddRenderSystem(this);
		break;
	case TRANSFORM_SYSTEM:
		m_pSystemManager->AddTransformSystem(this);
		break;
	}
}

template <typename T>
void ComponentSystem<T>::SetRenderQueue(RenderQueue* renderQueue)
{
	m_pRenderQueue = renderQueue;
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
		for(size_t i = 0; i < m_Components.GetSize();++i)
		{
			if(m_pEntityManager->IsAlive(m_EntityComponentLinks[i]))
			{
				m_ValidComps.push_back(i);
				continue;
			}

			m_CompsToDelete.push_back(i);
		}

		typename T::Soa soaStruct{};
		m_Components.FillSoaDefault(&soaStruct);

		for(size_t i : m_ValidComps)
		{
			OnUpdate(m_Components.GetSoa(&soaStruct, i), m_EntityComponentLinks[i]);
		}
	}
}

template <typename T>
void ComponentSystem<T>::LateUpdate()
{
	if (m_Components.GetSize() > 0)
	{
		typename T::Soa soaStruct;
		m_Components.FillSoaDefault(&soaStruct);

		for (size_t i : m_ValidComps)
		{
			OnLateUpdate(m_Components.GetSoa(&soaStruct, i), m_EntityComponentLinks[i]);
		}

		m_ValidComps.clear();
		CollectGarbage();
	}
}

template <typename T>
void ComponentSystem<T>::CleanUp()
{
	typename T::Soa soaStruct;
	m_Components.FillSoaDefault(&soaStruct);

	for (size_t i = 0; i < m_Components.GetSize(); ++i)
	{
		OnCleanUp(m_Components.GetSoa(&soaStruct, i));
	}
}

template <typename T>
void ComponentSystem<T>::Draw()
{
	if (m_Components.GetSize() > 0)
	{
		for (size_t i = 0; i < m_Components.GetSize(); ++i)
		{
			if (m_pEntityManager->IsAlive(m_EntityComponentLinks[i]))
			{
				m_ValidComps.push_back(i);
				continue;
			}

			m_CompsToDelete.push_back(i);
		}

		for (size_t i : m_ValidComps)
		{
			OnDraw(m_pRenderQueue, m_Components.GetAos(i), m_pSystemManager->GetTransform(m_EntityComponentLinks[i]));
		}

		m_ValidComps.clear();
		CollectGarbage();
	}
}

template <typename T>
size_t ComponentSystem<T>::GetComponentIndex(size_t entity)
{
	return std::find_if(m_EntityComponentLinks.begin(), m_EntityComponentLinks.end(), [entity](const auto& link) {return entity == link.second; })->second;
}

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
