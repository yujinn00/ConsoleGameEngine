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

	Level* GetPreviousLevel() const;
	void SetPreviousLevel(Level* level);

private:
	Level* lobbyLevel = nullptr;
	Level* gameLevel = nullptr;
	Level* guideLevel = nullptr;
	Level* rankLevel = nullptr;
	Level* menuLevel = nullptr;
	Level* overLevel = nullptr;
	Level* clearLevel = nullptr;

	Level* previousLevel = nullptr;

private:
	static Game* instance;
};
