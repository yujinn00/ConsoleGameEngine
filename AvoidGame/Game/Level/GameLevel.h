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
	// �� ���� �Լ�
	void SpawnEnemy();

	// ���� Ÿ�̸�
	float spawnElapsedTime = 0.0f;
	float spawnInterval = 0.0f;
};
