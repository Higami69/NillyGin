#pragma once
#include "Singleton.h"
#include <SDL.h>
#include <map>
#include <vector>

//TODO: Make input not global (possibly)

enum class InputType
{
	Release, //True one frame on release
	Press, //True one frame on press
	Down //True while down
};

struct Input
{
	size_t id;
	Uint8 key;
	InputType type;
};

class InputManager : public Singleton<InputManager>
{
public:
	InputManager() = default;

	void AddInput(Input input);
	void ResetTriggerInputs();
	void Update(SDL_KeyboardEvent event);
	bool IsActive(size_t id);

private:
	std::map<size_t,Uint64> m_InputFlags;
	std::multimap<Uint8, size_t> m_KeyIndexMap;
	std::map<size_t,InputType> m_InputTypes;
};