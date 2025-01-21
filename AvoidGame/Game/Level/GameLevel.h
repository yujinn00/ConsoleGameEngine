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

	// �÷��̾� ��ȯ �Լ�
	Player* GetPlayer() const;

private:
	// �׵θ� �׸��� �Լ�
	void DrawBorder();

	// ���� ���� �Լ�
	void SpawnEnemyA();
	void SpawnEnemyB();
	void SpawnEnemyC();
	void SpawnBomb();
	void SpawnShield();

	// ���ͳ����� �浹 ó��
	void ProcessCollisionPlayerAndEnemyA();
	void ProcessCollisionPlayerAndEnemyB();
	void ProcessCollisionPlayerAndEnemyC();
	void ProcessCollisionPlayerAndBullet();
	void ProcessCollisionEnemyAndBullet();
	void ProcessCollisionPlayerAndBomb();
	void ProcessCollisionPlayerAndShield();

private:
	// �÷��̾� ��ü
	Player* player;

	// ����
	int score = 0;

	// EnemyA ���� Ÿ�̸�
	float spawnElapsedTimeA = 0.0f;
	float spawnIntervalA = 0.0f;

	// EnemyB ���� Ÿ�̸�
	float spawnElapsedTimeB = 0.0f;
	float spawnIntervalB = 0.0f;

	// EnemyC ���� Ÿ�̸�
	float spawnElapsedTimeC = 0.0f;
	float spawnIntervalC = 0.0f;

	// Bomb ���� Ÿ�̸�
	float spawnElapsedTimeBomb = 0.0f;
	float spawnIntervalBomb = 0.0f;

	// Shield ���� Ÿ�̸�
	float spawnElapsedTimeShield = 0.0f;
	float spawnIntervalShield = 0.0f;
};
