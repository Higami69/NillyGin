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


int wmain(int argc, char *argv[])
{
	//Initialize
	srand((unsigned int)time(nullptr));

	auto entityManager = EntityManager{};
	auto systemManager = SystemManager{};
	auto inputManager = InputManager::GetInstance();
	auto eventManager = EventManager{};
	auto timeManager = TimeManager::GetInstance();

	RenderBackEnd renderBackEnd{};
	renderBackEnd.Initialize();
	RenderQueue renderQueue{};
	renderQueue.Initialize(&renderBackEnd);

	//Construct built in systems (so they're added to the systemManager)
#pragma region Built-In Systems
	auto transformSystem = new TransformComponentSystem();
	transformSystem->Initialize(&entityManager,&systemManager, &eventManager, "Transform", TRANSFORM_SYSTEM | IS_AFFECTED_BY_STATIC);
	auto moveSystem = new MovementComponentSystem();
	moveSystem->Initialize(&entityManager,&systemManager, &eventManager, "Move");
	auto renderPointSystem = new RenderPointComponentSystem();
	renderPointSystem->Initialize(&entityManager, &systemManager, &eventManager, "RenderPoint", RENDER_SYSTEM | IS_AFFECTED_BY_STATIC);
	renderPointSystem->SetRenderQueue(&renderQueue);
	auto renderLineSystem = new RenderLineComponentSystem();
	renderLineSystem->Initialize(&entityManager, &systemManager, &eventManager, "RenderLine", RENDER_SYSTEM | IS_AFFECTED_BY_STATIC);
	renderLineSystem->SetRenderQueue(&renderQueue);
	auto renderTriangleSystem = new RenderTriangleComponentSystem();
	renderTriangleSystem->Initialize(&entityManager, &systemManager, &eventManager, "RenderTriangle", RENDER_SYSTEM | IS_AFFECTED_BY_STATIC);
	renderTriangleSystem->SetRenderQueue(&renderQueue);
	auto renderRectangleSystem = new RenderRectangleComponentSystem();
	renderRectangleSystem->Initialize(&entityManager, &systemManager, &eventManager, "RenderRectangle", RENDER_SYSTEM | IS_AFFECTED_BY_STATIC);
	renderRectangleSystem->SetRenderQueue(&renderQueue);
	auto renderEllipseSystem = new RenderEllipseComponentSystem();
	renderEllipseSystem->Initialize(&entityManager, &systemManager, &eventManager, "RenderEllipse", RENDER_SYSTEM | IS_AFFECTED_BY_STATIC);
	renderEllipseSystem->SetRenderQueue(&renderQueue);
	auto renderTextureSystem = new RenderTextureComponentSystem();
	renderTextureSystem->Initialize(&entityManager, &systemManager, &eventManager, "RenderTexture", RENDER_SYSTEM | IS_AFFECTED_BY_STATIC);
	renderTextureSystem->SetRenderQueue(&renderQueue);
	auto rigidBodySystem = new RigidBodyComponentSystem();
	rigidBodySystem->Initialize(&entityManager, &systemManager, &eventManager, "RigidBody");
#pragma endregion

	SDL_GL_MakeCurrent(renderBackEnd.GetWindow(), renderBackEnd.GetContext());

	TextureLibrary texLib{};
	auto bram = texLib.LoadTexture("../Textures/GhostBram.png",GL_NEAREST);
	auto dorito = texLib.LoadTexture("../Textures/Dorito.png", GL_NEAREST);

	SDL_GL_MakeCurrent(0, 0);

	for(int i = 0; i < 1000; i++)
	{
		auto entity = entityManager.Create();
		RigidBodyComponent::Aos rigidBody;
		rigidBody.isStatic = true;
		rigidBodySystem->AddComponent(entity, rigidBody);
		TransformComponent::Aos transform;
		transform.pos.x = float(rand() % 600);
		transform.pos.y = float(rand() % 500);

		if(i > 499)
		{
			transform.pos.z = 1;
			transformSystem->AddComponent(entity, transform);
			RenderTextureComponent::Aos tex;
			tex.offset = Float2::Aos(0, 0);
			tex.dimensions = Float2::Aos(100.f + float(rand() % 200), 100.f + float(rand() % 200));
			tex.texId = dorito;
			renderTextureSystem->AddComponent(entity, tex);
		}
		else
		{
			transform.pos.z = 0;
			transformSystem->AddComponent(entity, transform);
			RenderTextureComponent::Aos tex;
			tex.offset = Float2::Aos(0, 0);
			tex.dimensions = Float2::Aos(100.f + float(rand() % 200), 100.f + float(rand() % 200));
			tex.texId = bram;
			renderTextureSystem->AddComponent(entity, tex);
		}
	}

	//Iniialize components
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
		renderBackEnd.Update();
	}

	//CleanUp
	renderBackEnd.CleanUp();
	systemManager.CleanUp();
	eventManager.Clear();
	TimeManager::DeleteInstance();
	InputManager::DeleteInstance();

	return 0;
}

