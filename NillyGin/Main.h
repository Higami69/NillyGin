#pragma once

#pragma region forward declarations
class EntityManager;
class SystemManager;
class EventManager;

class TransformComponentSystem;
class RenderPointComponentSystem;
class RenderLineComponentSystem;
class RenderTriangleComponentSystem;
class RenderRectangleComponentSystem;
class RenderEllipseComponentSystem;
class RenderTextureComponentSystem;
class RigidBodyComponentSystem;
#pragma endregion 

struct DefaultSystems
{
	TransformComponentSystem* transformSystem;
	RenderPointComponentSystem* renderPointSystem;
	RenderLineComponentSystem* renderLineSystem;
	RenderTriangleComponentSystem* renderTriangleSystem;
	RenderRectangleComponentSystem* renderRectangleSystem;
	RenderEllipseComponentSystem* renderEllipseSystem;
	RenderTextureComponentSystem* renderTextureSystem;
	RigidBodyComponentSystem* rigidBodySystem;
};

class ClientMain
{
public:

	static void Initialize(EntityManager* entityManager, SystemManager* systemManager ,EventManager* eventManager, const DefaultSystems& defaultSystems);
};