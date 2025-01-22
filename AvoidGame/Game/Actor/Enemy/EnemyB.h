#pragma once

#include "Actor/DrawableActor.h"

class EnemyB : public DrawableActor
{
	RTTI_DECLARATIONS(EnemyB, DrawableActor)

public:
	EnemyB(const char* image, SpawnPosition spawnPosition, float speed);

	virtual void Update(float deltaTime) override;

private:
	// x 좌표 및 y 좌표
	float xPosition;
	float yPosition;

	// 이동 속도
	float speed;

	// 이동 방향
	MoveDirection moveDirection = MoveDirection::None;

	// 생성 위치
	SpawnPosition spawnPosition;
};
