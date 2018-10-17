#pragma once
#include "Singleton.h"
#include <ctime>

class TimeManager : public Singleton<TimeManager>
{
public:
	TimeManager();

	void Update();
	float GetDeltaTime() const;

private:
	float m_DeltaTime;
	clock_t m_PreviousTime;
};
