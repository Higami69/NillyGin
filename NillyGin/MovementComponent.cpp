#include "pch.h"
#include "MovementComponent.h"
#include "InputManager.h"
#include "EventManager.h"
#include "TransformComponentSystem.h"

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
		eventManager->AddEvent("Transform", entity, new MoveEvent(Direction::LEFT, 1.f));
	}
	if (input->IsActive(1))
	{
		eventManager->AddEvent("Transform", entity, new MoveEvent(Direction::RIGHT, 1.f));
	}
	if (input->IsActive(2))
	{
		eventManager->AddEvent("Transform", entity, new MoveEvent(Direction::UP, 1.f));
	}
	if (input->IsActive(3))
	{
		eventManager->AddEvent("Transform", entity, new MoveEvent(Direction::DOWN, 1.f));
	}
}

void MovementComponentSystem::OnLateUpdate(MovementComponent::Soa* component, size_t entity)
{
}

void MovementComponentSystem::OnCleanUp(MovementComponent::Soa* component)
{
}
