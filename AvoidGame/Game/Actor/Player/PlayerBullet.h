#pragma once

#include <Actor/DrawableActor.h>

class PlayerBullet : public DrawableActor
{
	RTTI_DECLARATIONS(PlayerBullet, DrawableActor)

public:
	PlayerBullet(const Vector2& position, MoveDirection moveDirection);

	virtual void Update(float deltaTime) override;

private:
	// x ��ǥ
	float xPosition;

	// y ��ǥ
	float yPosition;

	// �̵� �ӵ�
	float speed = 50.0f;

	// �̵� ����
	MoveDirection moveDirection;
};
