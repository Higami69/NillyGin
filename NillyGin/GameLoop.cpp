#include "pch.h"
#include "EntityManager.h"
#include "SystemManager.h"
#include "TransformComponentSystem.h"
#include "InputManager.h"
#include "Tests.h"
#include "Renderer.h"
#include "RenderRectComponent.h"
#include "EventManager.h"
#include "MovementComponent.h"
#include "TimeManager.h"
#include "TextureComponent.h"


int wmain(int argc, char *argv[])
{
	//Initialize
	auto entityManager = EntityManager::GetInstance();
	auto systemManager = SystemManager::GetInstance();
	auto inputManager = InputManager::GetInstance();
	auto eventManager = EventManager::GetInstance();
	auto renderer = Renderer::GetInstance();
	auto timeManager = TimeManager::GetInstance();
	renderer->Initialize();

	//Construct built in systems (so they're added to the systemManager)
	auto transformSystem = new TransformComponentSystem();
	auto renderRectSystem = new RenderRectComponentSystem();
	auto moveSystem = new MovementComponentSystem();
	auto textureSystem = new TextureComponentSystem();

	{
		auto entity = entityManager->Create();
		TransformComponent::Aos transform;
		transform.xPos = 45;
		transform.yPos = 69;
		transformSystem->AddComponent(entity, transform);
		TextureComponent::Aos tex;
		tex.texture = renderer->LoadTexture("../Textures/bram.png");
		tex.width = 256.f;
		tex.height = 256.f;
		textureSystem->AddComponent(entity, tex);
		MovementComponent::Aos move;
		move.speed = 50.f;
		moveSystem->AddComponent(entity, move);
	}

	//Run
	bool isRunning = true;
	SDL_Event event;
	while(isRunning)
	{
		while(SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				isRunning = false; //TODO: Pass this somewhere else (to prompt user)
				break;
			case SDL_KEYDOWN:
			case SDL_KEYUP:
				inputManager->Update(event.key);
				break;
			default:
				break;
			}
		}

		timeManager->Update();
		systemManager->Update();
		inputManager->ResetTriggerInputs();
		eventManager->Clear();
		
		renderer->Display();
		renderer->ClearBackground();
	}

	//CleanUp
	renderer->CleanUp();
	systemManager->CleanUp();
	eventManager->Clear();
	Renderer::DeleteInstance();
	TimeManager::DeleteInstance();
	EntityManager::DeleteInstance();
	InputManager::DeleteInstance();
	SystemManager::DeleteInstance();
	EventManager::DeleteInstance();

	return 0;
}

