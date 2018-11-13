#include "pch.h"
#include "EntityManager.h"
#include "SystemManager.h"
#include "TransformComponentSystem.h"
#include "InputManager.h"
#include "Tests.h"
#include "Renderer.h"
#include "EventManager.h"
#include "MovementComponent.h"
#include "TimeManager.h"
#include "TextureComponent.h"
#include "RenderQueue.h"
#include "RenderBackEnd.h"
#include "RenderPointComponent.h"
#include "RenderLineComponent.h"
#include "RenderTriangleComponent.h"
#include "RenderRectangleComponent.h"
#include "RenderEllipseComponent.h"
#include "RenderTextureComponent.h"
#include "TextureLibrary.h"


int wmain(int argc, char *argv[])
{
	//Initialize
	srand((unsigned int)time(nullptr));

	auto entityManager = EntityManager{};
	auto systemManager = SystemManager{};
	auto inputManager = InputManager::GetInstance();
	auto eventManager = EventManager::GetInstance();
	auto timeManager = TimeManager::GetInstance();

	RenderBackEnd renderBackEnd{};
	renderBackEnd.Initialize();
	RenderQueue renderQueue{};
	renderQueue.Initialize(&renderBackEnd);

	//Construct built in systems (so they're added to the systemManager)
#pragma region Built-In Systems
	auto transformSystem = new TransformComponentSystem();
	transformSystem->Initialize(&entityManager,&systemManager,TRANSFORM_SYSTEM);
	auto moveSystem = new MovementComponentSystem();
	moveSystem->Initialize(&entityManager,&systemManager);
	auto renderPointSystem = new RenderPointComponentSystem();
	renderPointSystem->Initialize(&entityManager, &systemManager, RENDER_SYSTEM);
	renderPointSystem->SetRenderQueue(&renderQueue);
	auto renderLineSystem = new RenderLineComponentSystem();
	renderLineSystem->Initialize(&entityManager, &systemManager, RENDER_SYSTEM);
	renderLineSystem->SetRenderQueue(&renderQueue);
	auto renderTriangleSystem = new RenderTriangleComponentSystem();
	renderTriangleSystem->Initialize(&entityManager, &systemManager, RENDER_SYSTEM);
	renderTriangleSystem->SetRenderQueue(&renderQueue);
	auto renderRectangleSystem = new RenderRectangleComponentSystem();
	renderRectangleSystem->Initialize(&entityManager, &systemManager, RENDER_SYSTEM);
	renderRectangleSystem->SetRenderQueue(&renderQueue);
	auto renderEllipseSystem = new RenderEllipseComponentSystem();
	renderEllipseSystem->Initialize(&entityManager, &systemManager, RENDER_SYSTEM);
	renderEllipseSystem->SetRenderQueue(&renderQueue);
	auto renderTextureSystem = new RenderTextureComponentSystem();
	renderTextureSystem->Initialize(&entityManager, &systemManager, RENDER_SYSTEM);
	renderTextureSystem->SetRenderQueue(&renderQueue);
#pragma endregion

	SDL_GL_MakeCurrent(renderBackEnd.GetWindow(), renderBackEnd.GetContext());

	TextureLibrary texLib{};
	auto bram = texLib.LoadTexture("../Textures/GhostBram.png",GL_NEAREST);
	auto dorito = texLib.LoadTexture("../Textures/Dorito.png", GL_NEAREST);

	SDL_GL_MakeCurrent(0, 0);

	for(int i = 0; i < 1000; i++)
	{
		auto entity = entityManager.Create();
		TransformComponent::Aos transform;
		transform.pos.x = float(rand() % 600);
		transform.pos.y = float(rand() % 500);

		if(i > 499)
		{
			transform.pos.z = 0;
			transformSystem->AddComponent(entity, transform);
			RenderTextureComponent::Aos tex;
			tex.offset = Float2::Aos(0, 0);
			tex.dimensions = Float2::Aos(100.f + float(rand() % 200), 100.f + float(rand() % 200));
			tex.texId = dorito;
			renderTextureSystem->AddComponent(entity, tex);
		}
		else
		{
			transform.pos.z = 1;
			transformSystem->AddComponent(entity, transform);
			RenderTextureComponent::Aos tex;
			tex.offset = Float2::Aos(0, 0);
			tex.dimensions = Float2::Aos(100.f + float(rand() % 200), 100.f + float(rand() % 200));
			tex.texId = bram;
			renderTextureSystem->AddComponent(entity, tex);
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
		systemManager.Update();
		inputManager->ResetTriggerInputs();
		eventManager->Clear();
		
		renderQueue.Flush();
		renderBackEnd.Update();
	}

	//CleanUp
	renderBackEnd.CleanUp();
	systemManager.CleanUp();
	eventManager->Clear();
	TimeManager::DeleteInstance();
	InputManager::DeleteInstance();
	EventManager::DeleteInstance();

	return 0;
}

