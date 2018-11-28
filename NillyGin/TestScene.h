#pragma once
#include "GameScene.h"

class TransformComponentSystem;
class RenderTextureComponentSystem;
class RigidBodyComponentSystem;
class MovementComponentSystem;

class TestScene final : public GameScene
{
public:
	TestScene() = default;

	void SetSystems(TransformComponentSystem* transform, RenderTextureComponentSystem* tex,
		RigidBodyComponentSystem* rigidBody, MovementComponentSystem* move);
	void Load(EntityManager* pEntityManager) override;
private:
	TransformComponentSystem* m_pTransformSystem;
	RenderTextureComponentSystem* m_pRenderTextureSystem;
	RigidBodyComponentSystem* m_pRigidBodySystem;
	MovementComponentSystem* m_pMoveSystem;
};
