#pragma once

#include "Actor/DrawableActor.h"

// 위치와 이동 방향
enum class Direction
{
	Up,
	Down,
	Left,
	Right
};

class Enemy : public DrawableActor
{
	RTTI_DECLARATIONS(Enemy, DrawableActor)

public:
	Enemy(const char* image, float speed);

	virtual void Update(float deltaTime) override;

private:
	// x 좌표 및 y 좌표 계산
	float xPosition = 0.0f;
	float yPosition = 0.0f;

	// 이동 속도
	float speed = 0.0f;

	// 이동 방향
	Direction direction;
};
