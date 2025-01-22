#pragma once

#include "Actor/DrawableActor.h"

class EnemyA : public DrawableActor
{
	RTTI_DECLARATIONS(EnemyA, DrawableActor)

public:
	EnemyA(const char* image, float speed);

	virtual void Update(float deltaTime) override;

private:
	// x 좌표 및 y 좌표
	float xPosition;
	float yPosition;

	// 이동 속도
	float speed;

	// 이동 방향
	MoveDirection moveDirection = MoveDirection::None;
};
