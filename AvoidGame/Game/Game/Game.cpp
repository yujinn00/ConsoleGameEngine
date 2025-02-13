#include "Game.h"

#include "Level/LobbyLevel.h"
#include "Level/GameLevel.h"
#include "Level/GuideLevel.h"
#include "Level/RankLevel.h"
#include "Level/MenuLevel.h"
#include "Level/OverLevel.h"
#include "Level/ClearLevel.h"

Game* Game::instance = nullptr;

Game::Game()
	: Engine()
{
	SetCursorType(CursorType::NoCursor);

	instance = this;

	lobbyLevel = new LobbyLevel();
	gameLevel = new GameLevel();
	guideLevel = new GuideLevel();
	rankLevel = new RankLevel();
	menuLevel = new MenuLevel();
	overLevel = new OverLevel();
	clearLevel = new ClearLevel();
	mainLevel = lobbyLevel;
}

Game::~Game()
{
	mainLevel = nullptr;
	delete lobbyLevel;
	delete gameLevel;
	delete guideLevel;
	delete rankLevel;
	delete menuLevel;
	delete overLevel;
	delete clearLevel;
}

Level* Game::LoadLobbyLevel()
{
	return lobbyLevel;
}

void Game::ToggleLevel(const char* text)
{
	system("cls");

	SetPreviousLevel(mainLevel);

	if (text == "Start Game")
	{
		if (gameLevel)
		{
			delete gameLevel;
			gameLevel = nullptr;
		}
		gameLevel = new GameLevel();
		mainLevel = gameLevel;
	}
	else if (text == "Resume Game")
	{
		mainLevel = gameLevel;
	}
	else if (text == "Guide Line")
	{
		mainLevel = guideLevel;
	}
	else if (text == "ScoreBoard")
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
	else if (text == "Game Over")
	{
		mainLevel = overLevel;
	}
	else if (text == "Game Clear")
	{
		mainLevel = clearLevel;
	}
}

Level* Game::GetPreviousLevel() const
{
	return previousLevel;
}

void Game::SetPreviousLevel(Level* level)
{
	this->previousLevel = level;
}

void Game::SetScore(int score)
{
	this->score = score;
}

int Game::GetScore() const
{
	return score;
}
