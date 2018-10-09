#include "pch.h"
#include "EntityManager.h"
#include <cassert>

EntityManager::~EntityManager()
{
	m_FreeIndices.clear();
	m_Generations.clear();
}

size_t EntityManager::Create()
{
	size_t idx = 0;

	if(m_FreeIndices.size() > MINIMUM_FREE_INDICES)
	{
		idx = m_FreeIndices.front();
		m_FreeIndices.pop_front();
	}
	else
	{
		m_Generations.push_back(0);
		idx = m_Generations.size() - 1;
		assert(idx < (1 << ENTITY_INDEX_BITS));
	}

	return MakeEntity(idx, m_Generations[idx]);
}

void EntityManager::Destroy(size_t entity)
{	
	size_t idx = GET_INDEX(entity);
	++m_Generations[idx];
	m_FreeIndices.push_back(idx);
}

bool EntityManager::IsAlive(size_t entity)
{
	return m_Generations[GET_INDEX(entity)] == GET_GENERATION(entity);
}

size_t EntityManager::MakeEntity(size_t idx, size_t gen)
{
	size_t id = 0;
	id |= idx;
	id |= (gen << ENTITY_INDEX_BITS);
	return id;
}
