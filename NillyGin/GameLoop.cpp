#include "pch.h"
#include "EntityManager.h"
#include "SystemManager.h"
#include <SDL.h>
#include "TransformComponentSystem.h"
#include "InputManager.h"

#pragma comment(lib, "SDL2.lib")

int wmain(int argc, char *argv[])
{
	//Initialize
	auto entityManager = EntityManager::GetInstance();
	auto systemManager = SystemManager::GetInstance();
	auto inputManager = InputManager::GetInstance();

	SDL_Window* window = nullptr;
	SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);

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
	}

	//CleanUp
	SDL_DestroyWindow(window);
	systemManager->CleanUp();
	EntityManager::DeleteInstance();
	InputManager::DeleteInstance();
	SystemManager::DeleteInstance();

	return 0;
}

