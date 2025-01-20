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

	// �÷��̾�� ���Ϳ��� �浹 ó��
	void ProcessCollisionPlayerAndEnemyA();
	void ProcessCollisionPlayerAndEnemyB();
	void ProcessCollisionPlayerAndBullet();
	void ProcessCollisionPlayerAndEnemyC();

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
};
