#pragma once
#include "EventManager.h"

struct SetStaticEvent : public Event
{
	SetStaticEvent() : Event(0){};
};
