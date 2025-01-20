#include "Game/Game.h"

int main()
{
	// 메모리 누수 확인
	CheckMemoryLeak();

	Game game;
	game.LoadLevel(game.LoadLobbyLevel());
	game.Run();
}
