#include "pch.h"
#include "TimeManager.h"
#include <ctime>

TimeManager::TimeManager()
{
	m_PreviousTime = clock();
}

void TimeManager::Update()
{
	auto currTime = clock();
	m_DeltaTime = float(currTime - m_PreviousTime) / CLOCKS_PER_SEC;

	m_PreviousTime = currTime;
}

float TimeManager::GetDeltaTime() const
{
	return m_DeltaTime;
}
