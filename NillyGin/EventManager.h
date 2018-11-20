#pragma once
#include "Singleton.h"
#include <map>

struct Event
{
	Event(size_t id) : id(id) {};

	size_t id;
};

class EventManager
{
public:
	EventManager() = default;

	void AddQueue(std::string queueId);
	void AddEvent(std::string queueId, size_t entity, Event* event);
	std::multimap<size_t, Event*> GetEventQueue(std::string queueId);
	void Clear();

private:
	std::map<std::string ,std::multimap<size_t, Event*>> m_pEventQueues;
};