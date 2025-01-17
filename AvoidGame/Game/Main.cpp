#include "Game/Game.h"
#include "Level/GameLevel.h"

int main()
{
	Game game;
	game.LoadLevel(new GameLevel());
	game.Run();
}
