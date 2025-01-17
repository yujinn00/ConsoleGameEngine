#include "GameLevel.h"
#include "Engine/Engine.h"
#include "Actor/Player.h"
#include "Actor/Enemy.h"

GameLevel::GameLevel()
{
	AddActor(new Player("P"));

	// 초기 스폰 간격 설정
	spawnInterval = RandomPercent(1.0f, 3.0f);
}

GameLevel::~GameLevel()
{
}

void GameLevel::Update(float deltaTime)
{
	Super::Update(deltaTime);

	// ESC 종료
	if (Engine::Get().GetKeyDown(VK_ESCAPE))
	{
		Engine::Get().QuitGame();
	}

	// 적 스폰 타이머 업데이트
	spawnElapsedTime += deltaTime;
	if (spawnElapsedTime >= spawnInterval)
	{
		spawnElapsedTime = 0.0f;
		spawnInterval = RandomPercent(1.0f, 3.0f); // 새로운 랜덤 스폰 간격 설정
		SpawnEnemy(); // 적 생성
	}
}

void GameLevel::SpawnEnemy()
{
	// 적 생성
	float enemySpeed = RandomPercent(3.0f, 6.0f); // 속도 랜덤 설정
	AddActor(new Enemy("E", enemySpeed));
}
