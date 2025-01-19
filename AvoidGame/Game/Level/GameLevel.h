#pragma once

#include "Level/Level.h"

class GameLevel : public Level
{
	RTTI_DECLARATIONS(GameLevel, Level)

public:
	GameLevel();
	~GameLevel();

	virtual void Update(float deltaTime) override;

private:
	// EnemyA 생성 함수
	void SpawnEnemyA();

	// EnemyB 생성 함수
	void SpawnEnemyB();

	// 플레이어와 몬스터 A와의 충돌 처리
	void ProcessCollisionPlayerAndEnemyA();

	// 플레이어와 몬스터 B와의 충돌 처리
	void ProcessCollisionPlayerAndEnemyB();

	// 플레이어와 몬스터 총알과의 충돌 처리
	void ProcessCollisionPlayerAndBullet();

private:
	// EnemyA 스폰 타이머
	float spawnElapsedTimeA = 0.0f;
	float spawnIntervalA = 0.0f;

	// EnemyB 스폰 타이머
	float spawnElapsedTimeB = 0.0f;
	float spawnIntervalB = 0.0f;
};
