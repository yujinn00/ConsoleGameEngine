#pragma once

#include "Engine/Engine.h"

class Game : public Engine
{
public:
	Game();
	~Game();

	Level* LoadLobbyLevel();

	void ToggleLevel(const char* text);

	static Game& Get() { return *instance; }

private:
	Level* lobbyLevel = nullptr;
	Level* gameLevel = nullptr;
	Level* rankLevel = nullptr;
	Level* menuLevel = nullptr;

private:
	static Game* instance;
};
