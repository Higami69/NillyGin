#include "pch.h"
#include "EntityManager.h"
#include "SystemManager.h"
#include "TransformComponentSystem.h"
#include "InputManager.h"
#include "Tests.h"
#include "Renderer.h"


int wmain(int argc, char *argv[])
{
	//Initialize
	auto entityManager = EntityManager::GetInstance();
	auto systemManager = SystemManager::GetInstance();
	auto inputManager = InputManager::GetInstance();
	Renderer renderer{};
	renderer.Initialize();

	//Construct built in systems (so they're added to the systemManager)
	TransformComponentSystem{};

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

		systemManager->Update();
		inputManager->ResetTriggerInputs();
		
		renderer.DrawRectangle(0, 0, 50, 50,Colour(1,0,0,1));
		renderer.Display();
		renderer.ClearBackground();
	}

	//CleanUp
	renderer.CleanUp();
	systemManager->CleanUp();
	EntityManager::DeleteInstance();
	InputManager::DeleteInstance();
	SystemManager::DeleteInstance();

	return 0;
}

