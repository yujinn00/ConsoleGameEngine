#include "TestLevel.h"
#include "Engine/Engine.h"
#include "Actor/Player.h"
#include "Actor/Enemy.h"

TestLevel::TestLevel()
{
	AddActor(new Player("<A>"));
}

TestLevel::~TestLevel()
{
}

void TestLevel::Update(float deltaTime)
{
	Super::Update(deltaTime);

	// ���� ó�� (������ ù �������� �������� �ʾұ� ������, ���� ó���� �ؾ� ��)
	if (deltaTime > 1.0f)
	{
		return;
	}

	// ESC Ű�� ����
	if (Engine::Get().GetKeyDown(VK_ESCAPE))
	{
		Engine::Get().QuitGame();
	}

	// �� ����
	static float elapsedTime = 0.0f;
	static float spawnTime = RandomPercent(1.0f, 3.0f);

	// Ÿ�̸�
	elapsedTime += deltaTime;
	if (elapsedTime < spawnTime)
	{
		return;
	}

	// Ÿ�̸� ����
	elapsedTime = 0.0f;
	spawnTime = RandomPercent(1.0f, 3.0f);

	// �� ����
	AddActor(new Enemy("[[0]]", Random(1, 10)));
}
