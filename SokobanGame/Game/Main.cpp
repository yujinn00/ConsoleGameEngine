#include <iostream>
#include "Engine/Engine.h"
#include "Game/Game.h"
#include "Level/GameLevel.h"

int main()
{
	// �޸� ���� Ȯ��
	CheckMemoryLeak();

	Game game;
	game.LoadLevel(new GameLevel());
	game.Run();
}
