#include "pch.h"
#include "MovementComponent.h"
#include "InputManager.h"
#include "EventManager.h"
#include "TransformComponentSystem.h"
#include "TimeManager.h"

MovementComponentSystem::MovementComponentSystem()
{
	auto input = InputManager::GetInstance();
	input->AddInput(Input(0, SDL_SCANCODE_A, InputType::Down));
	input->AddInput(Input(1, SDL_SCANCODE_D, InputType::Down));
	input->AddInput(Input(2, SDL_SCANCODE_W, InputType::Down));
	input->AddInput(Input(3, SDL_SCANCODE_S, InputType::Down));

}

void MovementComponentSystem::OnUpdate(MovementComponent::Soa* component, size_t entity)
{
	auto input = InputManager::GetInstance();
	auto eventManager = EventManager::GetInstance();

	if(input->IsActive(0))
	{
		auto deltaTime = TimeManager::GetInstance()->GetDeltaTime();
		eventManager->AddEvent("Transform", entity, new MoveEvent(Direction::LEFT,*component->speed * deltaTime ));
	}
	if (input->IsActive(1))
	{
		auto deltaTime = TimeManager::GetInstance()->GetDeltaTime();
		eventManager->AddEvent("Transform", entity, new MoveEvent(Direction::RIGHT, *component->speed * deltaTime));
	}
	if (input->IsActive(2))
	{
		auto deltaTime = TimeManager::GetInstance()->GetDeltaTime();
		eventManager->AddEvent("Transform", entity, new MoveEvent(Direction::UP, *component->speed * deltaTime));
	}
	if (input->IsActive(3))
	{
		auto deltaTime = TimeManager::GetInstance()->GetDeltaTime();
		eventManager->AddEvent("Transform", entity, new MoveEvent(Direction::DOWN, *component->speed * deltaTime));
	}
}

void MovementComponentSystem::OnLateUpdate(MovementComponent::Soa* component, size_t entity)
{
}

void MovementComponentSystem::OnCleanUp(MovementComponent::Soa* component)
{
}

void MovementComponentSystem::OnDraw(RenderQueue* renderQueue, const MovementComponent::Aos& component, TransformComponent::Aos transform)
{
}
