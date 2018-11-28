#include "pch.h"
#include "Main.h"
#include "TestScene.h"
#include "MovementComponent.h"
#include "SceneManager.h"

void ClientMain::Initialize(EntityManager* entityManager, SystemManager* systemManager, EventManager* eventManager, const DefaultSystems& defaultSystems)
{
	auto sceneManager = SceneManager::GetInstance();

	auto moveSystem = new MovementComponentSystem();
	moveSystem->Initialize(entityManager, systemManager, eventManager, "Move");

	auto testScene = new TestScene();
	testScene->SetSystems(defaultSystems.transformSystem, defaultSystems.renderTextureSystem, defaultSystems.rigidBodySystem, moveSystem);
	sceneManager->AddScene("TestScene", testScene);

	sceneManager->SetActiveScene("TestScene");
}
