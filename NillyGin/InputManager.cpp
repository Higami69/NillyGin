#include "pch.h"
#include "InputManager.h"

#define FLAGS_ELEMENT_SIZE 32u
#define FLAGS_TRUE 1ll
#define FLAGS_FALSE 0ll

Input::Input(size_t id, Uint8 key, InputType type)
	:id(id), key(key), type(type)
{
}

void InputManager::AddInput(Input input)
{
	m_KeyIndexMap.emplace(input.key, input.id);
	m_InputTypes[input.id] = input.type;
}

void InputManager::ResetTriggerInputs()
{
	for(auto p : m_InputTypes)
	{
		if (p.second != InputType::Down)
		{
			m_InputFlags[p.first / FLAGS_ELEMENT_SIZE] |= FLAGS_TRUE << (p.first % FLAGS_ELEMENT_SIZE);
			m_InputFlags[p.first / FLAGS_ELEMENT_SIZE] &= FLAGS_FALSE << (p.first % FLAGS_ELEMENT_SIZE);
		}
	}
}

void InputManager::Update(SDL_KeyboardEvent event)
{
	auto range = m_KeyIndexMap.equal_range(event.keysym.scancode);
	auto it = range.first;

	do
	{
		if (it == m_KeyIndexMap.end()) return;

		auto type = m_InputTypes[it->second];
		if(event.type == SDL_KEYDOWN)
		{
			if (type == InputType::Down || type == InputType::Press) m_InputFlags[it->second / FLAGS_ELEMENT_SIZE] |= FLAGS_TRUE << (it->second % FLAGS_ELEMENT_SIZE);
			continue;
		}
		if (type == InputType::Release)
		{
			m_InputFlags[it->second / FLAGS_ELEMENT_SIZE] |= FLAGS_TRUE << (it->second % FLAGS_ELEMENT_SIZE);
			continue;
		}
		if (type == InputType::Down)
			m_InputFlags[it->second / FLAGS_ELEMENT_SIZE] &= FLAGS_FALSE << (it->second % FLAGS_ELEMENT_SIZE);
	} while (++it != range.second);
}

bool InputManager::IsActive(size_t id)
{
	return m_InputFlags[id / FLAGS_ELEMENT_SIZE] & FLAGS_TRUE << (id % FLAGS_ELEMENT_SIZE);
}
