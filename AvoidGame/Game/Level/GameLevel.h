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

	// �׵θ� �׸��� �Լ�
	void DrawBorder();

	// �÷��̾� ��ȯ �Լ�
	Player* GetPlayer() const;

	// ������ �����ϴ� �Լ�
	void SaveScore(int score);

private:
	// ���� ���� �Լ�
	void SpawnEnemyA();
	void SpawnEnemyB();
	void SpawnEnemyC();
	void SpawnBomb();
	void SpawnShield();
	void SpawnUpgrade();

	// ���ͳ����� �浹 ó��
	void ProcessCollisionPlayerAndEnemyA();
	void ProcessCollisionPlayerAndEnemyB();
	void ProcessCollisionPlayerAndEnemyC();
	void ProcessCollisionPlayerAndBullet();
	void ProcessCollisionEnemyAndBullet();
	void ProcessCollisionPlayerAndBomb();
	void ProcessCollisionPlayerAndShield();
	void ProcessCollisionPlayerAndUpgrade();

	// ���� ����
	void GameOver();

	// ���� Ŭ����
	void GameClear();

private:
	// �÷��̾� ��ü
	Player* player;

	// ����
	int score = 0;

	// ���� �ð�
	int remainingTime = 0;

	// ���� Ÿ�̸�
	float ElapsedTime = 0.0f;
	float scoreUpdateElapsedTime = 0.0f;

	// EnemyA ���� Ÿ�̸�
	float spawnElapsedTimeA = 0.0f;
	float spawnIntervalA = 1.0f;
	bool isRemovedEnemyA = false;

	// EnemyB ���� Ÿ�̸�
	float spawnElapsedTimeB = 0.0f;
	float spawnIntervalB = 20.0f;
	bool isRemovedEnemyB = false;

	// EnemyC ���� Ÿ�̸�
	float spawnElapsedTimeC = 0.0f;
	float spawnIntervalC = 40.0f;
	bool isRemovedEnemyC = false;

	// Bomb ���� Ÿ�̸�
	float spawnElapsedTimeBomb = 0.0f;
	float spawnIntervalBomb = 40.0f;

	// Shield ���� Ÿ�̸�
	float spawnElapsedTimeShield = 0.0f;
	float spawnIntervalShield = 20.0f;

	// Upgrade ���� Ÿ�̸�
	float spawnElapsedTimeUpgrade = 0.0f;
	float spawnIntervalUpgrade = 0.0f;
};
