#include "pch.h"
#include "EntityManager.h"
#include "SystemManager.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include "TransformComponentSystem.h"
#include "InputManager.h"
#include "Tests.h"

#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")
#pragma comment (lib,"opengl32.lib")
#pragma comment (lib,"Glu32.lib")
#pragma comment(lib, "SDL2_image.lib")  

int wmain(int argc, char *argv[])
{
	//Initialize
	auto entityManager = EntityManager::GetInstance();
	auto systemManager = SystemManager::GetInstance();
	auto inputManager = InputManager::GetInstance();

	SDL_Window* window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	SDL_GLContext context = SDL_GL_CreateContext(window);

	glClearColor(0,0,0,1);

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

		glClear(GL_COLOR_BUFFER_BIT);
		SDL_GL_SwapWindow(window);
	}

	//CleanUp
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	systemManager->CleanUp();
	EntityManager::DeleteInstance();
	InputManager::DeleteInstance();
	SystemManager::DeleteInstance();

	return 0;
}

