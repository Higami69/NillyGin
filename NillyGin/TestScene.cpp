#include "pch.h"
#include "TestScene.h"
#include "EntityManager.h"
#include "TransformComponentSystem.h"
#include "RenderTextureComponent.h"
#include "RigidBodyComponent.h"
#include "MovementComponent.h"

void TestScene::SetSystems(TransformComponentSystem* transform, RenderTextureComponentSystem* tex,
	RigidBodyComponentSystem* rigidBody, MovementComponentSystem* move)
{
	m_pTransformSystem = transform;
	m_pMoveSystem = move;
	m_pRenderTextureSystem = tex;
	m_pRigidBodySystem = rigidBody;
}

void TestScene::Load(EntityManager* pEntityManager)
{
	auto bram = m_TextureLibrary.LoadTexture("../Textures/GhostBram.png", GL_NEAREST);
	auto dorito = m_TextureLibrary.LoadTexture("../Textures/Dorito.png", GL_NEAREST);

	size_t entity = pEntityManager->Create();
	m_Entities.push_back(entity);
	TransformComponent::Aos transform{};
	transform.pos = Float3::Aos(200, 200, 1);
	m_pTransformSystem->AddComponent(entity, transform);
	MovementComponent::Aos mov{};
	mov.speed = 200.f;
	m_pMoveSystem->AddComponent(entity, mov);
	RenderTextureComponent::Aos tex{};
	tex.dimensions = Float2::Aos(200, 200);
	tex.offset = Float2::Aos(0, 0);
	tex.texId = dorito;
	m_pRenderTextureSystem->AddComponent(entity, tex);

	for(int i = 0; i < 1000; i++)
	{
		entity = pEntityManager->Create();
		m_Entities.push_back(entity);
		transform.pos = Float3::Aos(float(rand() % 600), float(rand() % 500), 0);
		m_pTransformSystem->AddComponent(entity, transform);
		tex.dimensions = Float2::Aos(float(rand() % 300 + 200),float(rand() % 300 + 200));
		tex.offset = Float2::Aos(0, 0);
		tex.texId = bram;
		m_pRenderTextureSystem->AddComponent(entity, tex);
		RigidBodyComponent::Aos rb{};
		rb.isStatic = true;
		m_pRigidBodySystem->AddComponent(entity, rb);
	}
}
