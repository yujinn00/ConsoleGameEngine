#pragma once

#include "Level/Level.h"

class TestLevel : public Level
{
	// RTTI ����
	RTTI_DECLARATIONS(TestLevel, Level)

public:
	TestLevel();
	~TestLevel();
	
	virtual void Update(float deltaTime) override;

private:
	// �� ���� �Լ�
	void SpawnEnemy(float deltaTime);

	// �÷��̾� ź��� ���� �浹 ó��
	void ProcessCollisionPlayerBulletAndEnemy();

	// �� ź��� �÷��̾��� �浹 ó��
	void ProcessCollisionPlayerAndEnemyBullet();

private:
	// ����
	int score = 0;
};
