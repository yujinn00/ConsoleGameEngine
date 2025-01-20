#pragma once

#include "Level/Level.h"

class Player;
class GameLevel : public Level
{
	RTTI_DECLARATIONS(GameLevel, Level)

public:
	GameLevel();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

	// 플레이어 반환 함수
	Player* GetPlayer() const;

private:
	// 테두리 그리기 함수
	void DrawBorder();

	// 몬스터 생성 함수
	void SpawnEnemyA();
	void SpawnEnemyB();
	void SpawnEnemyC();

	// 플레이어와 액터와의 충돌 처리
	void ProcessCollisionPlayerAndEnemyA();
	void ProcessCollisionPlayerAndEnemyB();
	void ProcessCollisionPlayerAndBullet();
	void ProcessCollisionPlayerAndEnemyC();

private:
	// 플레이어 객체
	Player* player;

	// EnemyA 스폰 타이머
	float spawnElapsedTimeA = 0.0f;
	float spawnIntervalA = 0.0f;

	// EnemyB 스폰 타이머
	float spawnElapsedTimeB = 0.0f;
	float spawnIntervalB = 0.0f;

	// EnemyC 스폰 타이머
	float spawnElapsedTimeC = 0.0f;
	float spawnIntervalC = 0.0f;
};
