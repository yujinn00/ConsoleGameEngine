#include <iostream>
#include "Engine/Engine.h"
#include "Level/GameLevel.h"

int main()
{
	// �޸� ���� Ȯ��
	CheckMemoryLeak();

	Engine engine;
	engine.LoadLevel(new GameLevel());
	engine.Run();
}
