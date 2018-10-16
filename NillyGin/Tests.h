#pragma once
#include "ComponentSystem.h"
#include "InputManager.h"
#include <iostream>

struct InputTestComponent
{
	struct Aos
	{
		char c;
	};
	struct Soa
	{
		char* c;
	};
};

DEFINE_SOA_CLASS(InputTestComponent,1)
DEFINE_SOA_TYPE(InputTestComponent,0,char,c)

class InputTestComponentSystem : public ComponentSystem<InputTestComponent>
{
	void OnUpdate(InputTestComponent::Soa* component, size_t entity) override
	{
		auto input = InputManager::GetInstance();
		if (input->IsActive(0)) std::cout << "REEEEEEE\n";
	}
	void OnLateUpdate(InputTestComponent::Soa* component, size_t entity) override
	{
		
	}
	void OnCleanUp(InputTestComponent::Soa* component) override
	{
		
	}
};