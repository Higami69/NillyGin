#pragma once
#include "Singleton.h"
#include <map>
#include <vector>

class GameScene;
class EntityManager;

class SceneManager : public Singleton<SceneManager>
{
public:
	SceneManager() = default;

	void Initialize(EntityManager* pEntityManager);

	void AddScene(std::string name, GameScene* scene);

	void SetActiveScene(std::string name); //Removes all currently loaded scenes
	void LoadScene(std::string name); //Loads scene on top of currently loaded scenes
	void UnloadScene(std::string name);

	void HandleLoading();

private:
	std::map<std::string, GameScene*> m_pScenes;
	std::vector<std::string> m_ActiveScenes, m_ScenesToLoad, m_ScenesToUnload;

	EntityManager* m_pEntityManager;
};
