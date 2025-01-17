#include "GameLevel.h"
#include "Engine/Engine.h"
#include "Actor/Player.h"
#include "Actor/Enemy.h"

GameLevel::GameLevel()
{
	AddActor(new Player("P"));

	// �ʱ� ���� ���� ����
	spawnInterval = RandomPercent(1.0f, 3.0f);
}

GameLevel::~GameLevel()
{
}

void GameLevel::Update(float deltaTime)
{
	Super::Update(deltaTime);

	// ESC ����
	if (Engine::Get().GetKeyDown(VK_ESCAPE))
	{
		Engine::Get().QuitGame();
	}

	// �� ���� Ÿ�̸� ������Ʈ
	spawnElapsedTime += deltaTime;
	if (spawnElapsedTime >= spawnInterval)
	{
		spawnElapsedTime = 0.0f;
		spawnInterval = RandomPercent(1.0f, 3.0f); // ���ο� ���� ���� ���� ����
		SpawnEnemy(); // �� ����
	}
}

void GameLevel::SpawnEnemy()
{
	// �� ����
	float enemySpeed = RandomPercent(3.0f, 6.0f); // �ӵ� ���� ����
	AddActor(new Enemy("E", enemySpeed));
}
