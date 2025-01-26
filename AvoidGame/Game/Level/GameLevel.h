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

	// 테두리 그리기 함수
	void DrawBorder();

	// 플레이어 반환 함수
	Player* GetPlayer() const;

	// 점수를 저장하는 함수
	void SaveScore(int score);

private:
	// 액터 생성 함수
	void SpawnEnemyA();
	void SpawnEnemyB();
	void SpawnEnemyC();
	void SpawnBomb();
	void SpawnShield();
	void SpawnUpgrade();

	// 액터끼리의 충돌 처리
	void ProcessCollisionPlayerAndEnemyA();
	void ProcessCollisionPlayerAndEnemyB();
	void ProcessCollisionPlayerAndEnemyC();
	void ProcessCollisionPlayerAndBullet();
	void ProcessCollisionEnemyAndBullet();
	void ProcessCollisionPlayerAndBomb();
	void ProcessCollisionPlayerAndShield();
	void ProcessCollisionPlayerAndUpgrade();

	// 게임 오버
	void GameOver();

	// 게임 클리어
	void GameClear();

private:
	// 플레이어 객체
	Player* player;

	// 점수
	int score = 0;

	// 남은 시간
	int remainingTime = 0;

	// 게임 타이머
	float ElapsedTime = 0.0f;
	float scoreUpdateElapsedTime = 0.0f;

	// EnemyA 스폰 타이머
	float spawnElapsedTimeA = 0.0f;
	float spawnIntervalA = 1.0f;
	bool isRemovedEnemyA = false;

	// EnemyB 스폰 타이머
	float spawnElapsedTimeB = 0.0f;
	float spawnIntervalB = 20.0f;
	bool isRemovedEnemyB = false;

	// EnemyC 스폰 타이머
	float spawnElapsedTimeC = 0.0f;
	float spawnIntervalC = 40.0f;
	bool isRemovedEnemyC = false;

	// Bomb 스폰 타이머
	float spawnElapsedTimeBomb = 0.0f;
	float spawnIntervalBomb = 40.0f;

	// Shield 스폰 타이머
	float spawnElapsedTimeShield = 0.0f;
	float spawnIntervalShield = 20.0f;

	// Upgrade 스폰 타이머
	float spawnElapsedTimeUpgrade = 0.0f;
	float spawnIntervalUpgrade = 0.0f;
};
