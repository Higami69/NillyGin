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
	srand((unsigned int)time(nullptr));

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

	for(int i = 0; i < 1000; i++)
	{
		auto entity = entityManager->Create();
		TransformComponent::Aos transform;
		transform.xPos = (float) (rand() % 600);
		transform.yPos = (float)(rand() % 500);
		transformSystem->AddComponent(entity, transform);
		if (i > 0)
		{
			RenderRectComponent::Aos rect;
			rect.width = (float) (rand() % 250) + 20;
			rect.height = (float)(rand() % 150) + 20;
			rect.color_a = 1.f;
			rect.color_b = (float)(rand() % 255) / 255.f;
			rect.color_g = (float)(rand() % 255) / 255.f;
			rect.color_r = (float)(rand() % 255) / 255.f;
			renderRectSystem->AddComponent(entity, rect);
		}
		else
		{
			MovementComponent::Aos move;
			move.speed = 500.f;
			moveSystem->AddComponent(entity, move);
			TextureComponent::Aos tex;
			tex.texture = renderer->LoadTexture("../Textures/GhostBram.png");
			tex.width = 128.f;
			tex.height = 128.f;
			textureSystem->AddComponent(entity, tex);
		}
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

