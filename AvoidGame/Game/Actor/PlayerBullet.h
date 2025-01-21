#pragma once

#include <Actor/DrawableActor.h>

class PlayerBullet : public DrawableActor
{
	RTTI_DECLARATIONS(PlayerBullet, DrawableActor)

public:
	PlayerBullet(const Vector2& position, MoveDirection moveDirection, float speed);

	virtual void Update(float deltaTime) override;

private:
	// x 좌표
	float xPosition = 0.0f;

	// y 좌표
	float yPosition = 0.0f;

	// 이동 속도
	float speed = 30.0f;

	// 이동 방향
	MoveDirection moveDirection;
};
