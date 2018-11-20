#pragma once
#include "Singleton.h"
#include "DataBlockSoa.h"
#include <vector>
#include <thread>
#include <map>
#include "SystemManager.h"
#include "EntityManager.h"
#include <algorithm>
#include "EventManager.h"

#define RENDER_SYSTEM 0x0001u
#define TRANSFORM_SYSTEM 0x0002u
#define IS_AFFECTED_BY_STATIC 0x0004u

class RenderQueue;

class ComponentSystemInterface
{
public:
	virtual ~ComponentSystemInterface() = default;

	virtual void InitializeComps() = 0;
	virtual void PostInitializeComps() = 0;
	virtual void Update() = 0;
	virtual void LateUpdate() = 0;
	virtual void CleanUp() = 0;
	virtual void Draw() = 0;
	virtual void DrawStatic() = 0;

	virtual size_t GetComponentIndex(size_t entity) = 0;
	virtual size_t GetComponentIndexStatic(size_t entity) = 0;
};

template<typename T>
class ComponentSystem : public ComponentSystemInterface
{
public:
	ComponentSystem();
	virtual ~ComponentSystem();

	void Initialize(EntityManager* entityManager,SystemManager* systemManager, EventManager* eventManager, std::string eventQueueId, size_t flags = 0u);
	void SetRenderQueue(RenderQueue* renderQueue);

	void AddComponent(size_t entity, const typename T::Aos& component);

	void InitializeComps() override;
	void PostInitializeComps() override;
	void Update() override;
	void LateUpdate() override;
	void CleanUp() override;
	void Draw() override;
	void DrawStatic() override;

	size_t GetComponentIndex(size_t entity) override;
	size_t GetComponentIndexStatic(size_t entity) override;

	virtual void OnInitialize(EventManager* eventManager, const typename T::Aos& component, size_t entity) = 0;
	virtual void OnPostInitialize(std::multimap < size_t, Event*>::_Pairii events, typename T::Soa* component, size_t entity) = 0;
	virtual void OnUpdate(EventManager* eventManager, const typename T::Aos& component, size_t entity) = 0;
	virtual void OnLateUpdate(std::multimap < size_t, Event*>::_Pairii events, typename T::Soa* component, size_t entity) = 0;
	virtual void OnCleanUp(typename T::Soa* component) = 0;
	virtual void OnDraw(RenderQueue* renderQueue, const typename T::Aos& component, TransformComponent::Aos transform) = 0;

protected:
	DataBlockSoa<T> m_Components, m_StaticComponents;

private:
	void CollectGarbage();

private:
	std::vector<size_t> m_CompsToDelete, m_ValidComps;
	std::map<size_t,size_t> m_EntityComponentLinks, m_StaticEntityComponentLinks; //left = ComponentId, right = EntityId

	EntityManager* m_pEntityManager;
	SystemManager* m_pSystemManager;
	EventManager* m_pEventManager;
	RenderQueue* m_pRenderQueue = nullptr;

	std::string m_EventQueueId;
	size_t m_Flags;
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
void ComponentSystem<T>::Initialize(EntityManager* entityManager, SystemManager* systemManager, EventManager* eventManager, std::string eventQueueId, size_t flags)
{
	m_pEntityManager = entityManager;
	m_pSystemManager = systemManager;
	m_pEventManager = eventManager;
	m_EventQueueId = eventQueueId;
	m_Flags = flags;
	
	m_pEventManager->AddQueue(m_EventQueueId);

	if(m_Flags & RENDER_SYSTEM)
		m_pSystemManager->AddRenderSystem(this);
	else if(m_Flags & TRANSFORM_SYSTEM)
		m_pSystemManager->AddTransformSystem(this);
	else
		m_pSystemManager->AddSystem(this);
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
void ComponentSystem<T>::InitializeComps()
{
	if(m_Components.GetSize() > 0)
	{
		for(size_t i = 0; i < m_Components.GetSize(); ++i)
		{
			OnInitialize(m_pEventManager, m_Components.GetAos(i), m_EntityComponentLinks[i]);
		}
	}
}

template <typename T>
void ComponentSystem<T>::PostInitializeComps()
{
	if (m_Components.GetSize() > 0)
	{
		//Default post-initialize
		typename T::Soa soaStruct{};
		m_Components.FillSoaDefault(&soaStruct);

		auto eventQueue = m_pEventManager->GetEventQueue(m_EventQueueId);

		for (size_t i = 0; i < m_Components.GetSize(); ++i)
		{
			auto events = eventQueue.equal_range(m_EntityComponentLinks[i]);
			if (events.first == eventQueue.end()) continue;

			OnPostInitialize(events, m_Components.GetSoa(&soaStruct,i), m_EntityComponentLinks[i]);
		}

		//Check what components are static if affected
		if(m_Flags & IS_AFFECTED_BY_STATIC)
		{
			eventQueue = m_pEventManager->GetEventQueue("Static");

			for(size_t i = 0; i < m_Components.GetSize(); i++)
			{
				auto events = eventQueue.equal_range(m_EntityComponentLinks[i]);
				if (events.first == eventQueue.end()) continue;

				m_StaticComponents.Add(m_Components.GetAos(i));
				m_StaticEntityComponentLinks[i] = m_EntityComponentLinks[i];
				m_CompsToDelete.push_back(i);
			}
			CollectGarbage();
		}
	}
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

		for(size_t i : m_ValidComps)
		{
			OnUpdate(m_pEventManager, m_Components.GetAos(i), m_EntityComponentLinks[i]);
		}
	}
}

template <typename T>
void ComponentSystem<T>::LateUpdate()
{
	if (m_ValidComps.size() > 0)
	{
		typename T::Soa soaStruct;
		m_Components.FillSoaDefault(&soaStruct);

		auto eventQueue = m_pEventManager->GetEventQueue(m_EventQueueId);

		for (size_t i : m_ValidComps)
		{
			auto events = eventQueue.equal_range(m_EntityComponentLinks[i]);
			if (events.first == eventQueue.end()) continue;

			OnLateUpdate(events, m_Components.GetSoa(&soaStruct, i), m_EntityComponentLinks[i]);
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
void ComponentSystem<T>::DrawStatic()
{
	if(m_StaticComponents.GetSize() > 0)
	{
		for(size_t i = 0; i < m_StaticComponents.GetSize(); i++)
		{
			if(m_pEntityManager->IsAlive(m_StaticEntityComponentLinks[i]))
			{
				m_ValidComps.push_back(i);
				continue;
			}

			m_CompsToDelete.push_back(i);
		}

		for(size_t i : m_ValidComps)
		{
			OnDraw(m_pRenderQueue, m_StaticComponents.GetAos(i), m_pSystemManager->GetTransformStatic(m_StaticEntityComponentLinks[i]));
		}

		m_ValidComps.clear();

		//Delete comps that need to be deleted
		for (size_t i : m_CompsToDelete)
		{
			size_t last;
			do
			{
				last = m_StaticComponents.Remove(i);
				m_StaticEntityComponentLinks[i] = m_StaticEntityComponentLinks[last];
				m_StaticEntityComponentLinks.erase(m_StaticEntityComponentLinks.find(last));
			} while (std::find(m_CompsToDelete.begin(), m_CompsToDelete.end(), last) != m_CompsToDelete.end());
		}
		m_CompsToDelete.clear();
	}
}

template <typename T>
size_t ComponentSystem<T>::GetComponentIndex(size_t entity)
{
	return std::find_if(m_EntityComponentLinks.begin(), m_EntityComponentLinks.end(), [entity](const auto& link) {return entity == link.second; })->second;
}

template <typename T>
size_t ComponentSystem<T>::GetComponentIndexStatic(size_t entity)
{
	return std::find_if(m_StaticEntityComponentLinks.begin(), m_StaticEntityComponentLinks.end(), [entity](const auto& link) {return entity == link.second; })->second;
}

template <typename T>
void ComponentSystem<T>::CollectGarbage()
{
	while(m_CompsToDelete.size() > 0)
	{
		size_t last;
		size_t idx = m_CompsToDelete[0];
		do
		{
			last = m_Components.Remove(idx);
			m_EntityComponentLinks[idx] = m_EntityComponentLinks[last];
			m_EntityComponentLinks.erase(m_EntityComponentLinks.find(last));
			m_CompsToDelete.erase(std::remove(m_CompsToDelete.begin(), m_CompsToDelete.end(), idx));
			idx = last;
		} while (std::find(m_CompsToDelete.begin(), m_CompsToDelete.end(), last) != m_CompsToDelete.end());
	}
	m_CompsToDelete.clear();
}
