#include "Game/Game.h"
#include "Level/TestLevel.h"

int main()
{
	// �޸� ���� Ȯ��
	CheckMemoryLeak();

	Game game;
	game.LoadLevel(new TestLevel());
	game.Run();
}
