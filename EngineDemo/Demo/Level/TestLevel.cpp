#include "TestLevel.h"
#include "Engine/Engine.h"
#include "Core.h"

TestLevel::TestLevel()
{
}

TestLevel::~TestLevel()
{
}

void TestLevel::Update(float deltaTime)
{
	Level::Update(deltaTime);

	// ESC Ű�� ����
	if (Engine::Get().GetKeyDown(VK_ESCAPE))
	{
		Engine::Get().QuitGame();
	}
}
