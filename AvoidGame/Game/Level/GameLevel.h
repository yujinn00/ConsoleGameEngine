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
	// EnemyA ���� �Լ�
	void SpawnEnemyA();

	// EnemyB ���� �Լ�
	void SpawnEnemyB();

	// �÷��̾�� ���� A���� �浹 ó��
	void ProcessCollisionPlayerAndEnemyA();

	// �÷��̾�� ���� B���� �浹 ó��
	void ProcessCollisionPlayerAndEnemyB();

	// �÷��̾�� ���� �Ѿ˰��� �浹 ó��
	void ProcessCollisionPlayerAndBullet();

private:
	// EnemyA ���� Ÿ�̸�
	float spawnElapsedTimeA = 0.0f;
	float spawnIntervalA = 0.0f;

	// EnemyB ���� Ÿ�̸�
	float spawnElapsedTimeB = 0.0f;
	float spawnIntervalB = 0.0f;
};
