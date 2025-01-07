#include "Game/Game.h"
#include "Level/TestLevel.h"

int main()
{
	Engine engine;
	engine.LoadLevel(new TestLevel());
	engine.Run();

	//Game game;
	//game.LoadLevel(new TestLevel());
	//game.Run();
}
