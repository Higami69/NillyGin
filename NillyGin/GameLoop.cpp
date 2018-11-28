#include "pch.h"
#include "EntityManager.h"
#include "SystemManager.h"
#include "TransformComponentSystem.h"
#include "InputManager.h"
#include "Renderer.h"
#include "EventManager.h"
#include "MovementComponent.h"
#include "TimeManager.h"
#include "RenderQueue.h"
#include "RenderBackEnd.h"
#include "RenderPointComponent.h"
#include "RenderLineComponent.h"
#include "RenderTriangleComponent.h"
#include "RenderRectangleComponent.h"
#include "RenderEllipseComponent.h"
#include "RenderTextureComponent.h"
#include "TextureLibrary.h"
#include "RigidBodyComponent.h"
#include "SceneManager.h"
#include "Main.h"


int wmain(int argc, char *argv[])
{
	//Initialize
	srand((unsigned int)time(nullptr));

	auto entityManager = EntityManager{};
	auto systemManager = SystemManager{};
	auto inputManager = InputManager::GetInstance();
	auto eventManager = EventManager{};
	auto timeManager = TimeManager::GetInstance();
	auto sceneManager = SceneManager::GetInstance();

	RenderBackEnd renderBackEnd{};
	renderBackEnd.Initialize();
	RenderQueue renderQueue{};
	renderQueue.Initialize(&renderBackEnd);
	sceneManager->Initialize(&entityManager);

	//Construct built in systems (so they're added to the systemManager)
#pragma region Built-In Systems
	DefaultSystems systems{};
	systems.transformSystem = new TransformComponentSystem();
	systems.transformSystem->Initialize(&entityManager,&systemManager, &eventManager, "Transform", TRANSFORM_SYSTEM | IS_AFFECTED_BY_STATIC);
	systems.renderPointSystem = new RenderPointComponentSystem();
	systems.renderPointSystem->Initialize(&entityManager, &systemManager, &eventManager, "RenderPoint", RENDER_SYSTEM | IS_AFFECTED_BY_STATIC);
	systems.renderPointSystem->SetRenderQueue(&renderQueue);
	systems.renderLineSystem = new RenderLineComponentSystem();
	systems.renderLineSystem->Initialize(&entityManager, &systemManager, &eventManager, "RenderLine", RENDER_SYSTEM | IS_AFFECTED_BY_STATIC);
	systems.renderLineSystem->SetRenderQueue(&renderQueue);
	systems.renderTriangleSystem = new RenderTriangleComponentSystem();
	systems.renderTriangleSystem->Initialize(&entityManager, &systemManager, &eventManager, "RenderTriangle", RENDER_SYSTEM | IS_AFFECTED_BY_STATIC);
	systems.renderTriangleSystem->SetRenderQueue(&renderQueue);
	systems.renderRectangleSystem = new RenderRectangleComponentSystem();
	systems.renderRectangleSystem->Initialize(&entityManager, &systemManager, &eventManager, "RenderRectangle", RENDER_SYSTEM | IS_AFFECTED_BY_STATIC);
	systems.renderRectangleSystem->SetRenderQueue(&renderQueue);
	systems.renderEllipseSystem = new RenderEllipseComponentSystem();
	systems.renderEllipseSystem->Initialize(&entityManager, &systemManager, &eventManager, "RenderEllipse", RENDER_SYSTEM | IS_AFFECTED_BY_STATIC);
	systems.renderEllipseSystem->SetRenderQueue(&renderQueue);
	systems.renderTextureSystem = new RenderTextureComponentSystem();
	systems.renderTextureSystem->Initialize(&entityManager, &systemManager, &eventManager, "RenderTexture", RENDER_SYSTEM | IS_AFFECTED_BY_STATIC);
	systems.renderTextureSystem->SetRenderQueue(&renderQueue);
	systems.rigidBodySystem = new RigidBodyComponentSystem();
	systems.rigidBodySystem->Initialize(&entityManager, &systemManager, &eventManager, "RigidBody");
#pragma endregion

	SDL_GL_MakeCurrent(renderBackEnd.GetWindow(), renderBackEnd.GetContext());

	ClientMain::Initialize(&entityManager, &systemManager, &eventManager, systems);
	sceneManager->HandleLoading();

	SDL_GL_MakeCurrent(0, 0);

	//Initialize components
	systemManager.Initialize();
	renderQueue.FlushToPersistent();

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
		eventManager.Clear();
		
		renderQueue.Flush();
		renderBackEnd.PauseThread();
		SDL_GL_MakeCurrent(renderBackEnd.GetWindow(), renderBackEnd.GetContext());
		sceneManager->HandleLoading();
		SDL_GL_MakeCurrent(0, 0);
		renderBackEnd.ResumeThread();
	}

	//CleanUp
	renderBackEnd.CleanUp();
	systemManager.CleanUp();
	eventManager.Clear();
	TimeManager::DeleteInstance();
	InputManager::DeleteInstance();

	return 0;
}

