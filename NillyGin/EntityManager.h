#pragma once
#include "Singleton.h"
#include <deque>
#include <vector>

#define ENTITY_INDEX_BITS 24u
#define ENTITY_GENERATION_BITS 8u

#define ENTITY_INDEX_MASK ((1u << ENTITY_INDEX_BITS) - 1u)
#define ENTITY_GENERATION_MASK ((1u << ENTITY_GENERATION_BITS) - 1u)

#define GET_INDEX(entity) (entity & ENTITY_INDEX_MASK)
#define GET_GENERATION(entity) ((entity >> ENTITY_INDEX_BITS) & ENTITY_GENERATION_MASK)

#define MINIMUM_FREE_INDICES 1024u

class EntityManager
{
public:
	EntityManager() = default;
	~EntityManager();

	size_t Create();
	void Destroy(size_t entity);
	
	bool IsAlive(size_t entity);

private:
	size_t MakeEntity(size_t idx, size_t gen);

private:
	std::vector<unsigned char> m_Generations;
	std::deque<size_t> m_FreeIndices;
};