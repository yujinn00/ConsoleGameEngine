#include "Game.h"

#include "Level/LobbyLevel.h"
#include "Level/GameLevel.h"
#include "Level/MenuLevel.h"
//#include "Level/ScoreLevel.h"

Game* Game::instance = nullptr;

Game::Game()
	: Engine()
{
	SetCursorType(CursorType::NoCursor);

	instance = this;

	lobbyLevel = new LobbyLevel();
	gameLevel = new GameLevel();
	menuLevel = new MenuLevel();
	//scoreLevel = new ScoreLevel();
	mainLevel = lobbyLevel;
}

Game::~Game()
{
	mainLevel = nullptr;
	delete lobbyLevel;
	delete gameLevel;
	delete menuLevel;
	//delete scoreLevel;
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
	else if (text == "Game Menu")
	{
		mainLevel = menuLevel;
	}
	else if (text == "Return to Lobby")
	{
		mainLevel = lobbyLevel;
	}
	//else if (text == "ScoreBoard")
	//{
	//	mainLevel = scoreLevel;
	//}
}
