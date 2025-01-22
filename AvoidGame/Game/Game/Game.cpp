#include "Game.h"

#include "Level/LobbyLevel.h"
#include "Level/GameLevel.h"
#include "Level/RankLevel.h"
#include "Level/MenuLevel.h"

Game* Game::instance = nullptr;

Game::Game()
	: Engine()
{
	SetCursorType(CursorType::NoCursor);

	instance = this;

	lobbyLevel = new LobbyLevel();
	gameLevel = new GameLevel();
	rankLevel = new RankLevel();
	menuLevel = new MenuLevel();
	mainLevel = lobbyLevel;
}

Game::~Game()
{
	mainLevel = nullptr;
	delete lobbyLevel;
	delete gameLevel;
	delete rankLevel;
	delete menuLevel;
}

Level* Game::LoadLobbyLevel()
{
	return lobbyLevel;
}

void Game::ToggleLevel(const char* text)
{
	system("cls");

	if (text == "Start Game" || text == "Resume Game")
	{
		mainLevel = gameLevel;
	}
	else if (text == "Rank Rank")
	{
		mainLevel = rankLevel;
	}
	else if (text == "Game Menu")
	{
		mainLevel = menuLevel;
	}
	else if (text == "Return to Lobby")
	{
		mainLevel = lobbyLevel;
	}
}
