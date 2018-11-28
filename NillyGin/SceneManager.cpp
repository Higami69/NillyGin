#include "pch.h"
#include "SceneManager.h"
#include "GameScene.h"
#include <algorithm>

void SceneManager::Initialize(EntityManager* pEntityManager)
{
	m_pEntityManager = pEntityManager;
}

void SceneManager::AddScene(std::string name, GameScene* scene)
{
	m_pScenes.emplace(name, scene);
}

void SceneManager::SetActiveScene(std::string name)
{
	for(std::string s : m_ActiveScenes)
	{
		m_ScenesToUnload.push_back(s);
	}

	m_ScenesToLoad.push_back(name);
}

void SceneManager::LoadScene(std::string name)
{
	m_ScenesToLoad.push_back(name);
}

void SceneManager::UnloadScene(std::string name)
{
	m_ScenesToUnload.push_back(name);
}

void SceneManager::HandleLoading()
{
	for(std::string s : m_ScenesToUnload)
	{
		auto it = std::remove(m_ActiveScenes.begin(), m_ActiveScenes.end(), s);
		if (it == m_ActiveScenes.end()) continue;

		m_ActiveScenes.erase(it);
		m_pScenes[s]->Unload(m_pEntityManager);
	}

	for(std::string s : m_ScenesToLoad)
	{
		m_pScenes[s]->Load(m_pEntityManager);
		m_ActiveScenes.push_back(s);
	}

	m_ScenesToLoad.clear();
	m_ScenesToUnload.clear();
}
