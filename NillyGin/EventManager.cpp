#include "pch.h"
#include "EventManager.h"

void EventManager::AddQueue(std::string queueId)
{
	m_pEventQueues[queueId] = std::multimap<size_t,Event*>{};
}

void EventManager::AddEvent(std::string queueId, size_t entity, Event* event)
{
	m_pEventQueues[queueId].emplace(entity, event);
}

std::multimap<size_t, Event*> EventManager::GetEventQueue(std::string queueId)
{
	return m_pEventQueues[queueId];
}

void EventManager::Clear()
{
	for(auto it = m_pEventQueues.begin();it != m_pEventQueues.end();it++)
	{
		for(auto i = it->second.begin();i != it->second.end();i++)
		{
			delete i->second;
		}
		it->second.clear();
	}
	m_pEventQueues.clear();
}
