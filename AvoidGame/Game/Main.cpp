#include "Game/Game.h"

int main()
{
	// �޸� ���� Ȯ��
	CheckMemoryLeak();

	Game game;
	game.LoadLevel(game.LoadLobbyLevel());
	game.Run();
}
