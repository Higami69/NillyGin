#pragma once
#include <vector>
#include "TextureLibrary.h"

class EntityManager;

class GameScene
{
public:
	GameScene() = default;
	virtual ~GameScene() = default;

	virtual void Load(EntityManager* pEntityManager) = 0;
	void Unload(EntityManager* pEntityManager);

protected:
	std::vector<size_t> m_Entities;
	TextureLibrary m_TextureLibrary;
};
