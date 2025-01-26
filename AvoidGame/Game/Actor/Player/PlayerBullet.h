#pragma once

#include <Actor/DrawableActor.h>

class PlayerBullet : public DrawableActor
{
	RTTI_DECLARATIONS(PlayerBullet, DrawableActor)

public:
	PlayerBullet(const Vector2& position, MoveDirection moveDirection);

	virtual void Update(float deltaTime) override;

private:
	// x 좌표
	float xPosition;

	// y 좌표
	float yPosition;

	// 이동 속도
	float speed = 50.0f;

	// 이동 방향
	MoveDirection moveDirection;
};
