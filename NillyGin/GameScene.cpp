#include "pch.h"
#include "GameScene.h"
#include "EntityManager.h"

void GameScene::Unload(EntityManager* pEntityManager)
{
	for(size_t entity : m_Entities)
	{
		pEntityManager->Destroy(entity);
	}

	m_Entities.clear();

	m_TextureLibrary.FreeTextures();
}
