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
	// 적 생성 함수
	void SpawnEnemy();

	// 스폰 타이머
	float spawnElapsedTime = 0.0f;
	float spawnInterval = 0.0f;
};
