#pragma once

#include <Actor/DrawableActor.h>

class EnemyBullet : public DrawableActor
{
	RTTI_DECLARATIONS(EnemyBullet, DrawableActor)

public:
	EnemyBullet(const Vector2& position, MoveDirection moveDirection);

	virtual void Update(float deltaTime) override;

private:
	// x ��ǥ
	float xPosition;

	// y ��ǥ
	float yPosition;

	// �̵� �ӵ�
	float speed = 10.0f;

	// �̵� ����
	MoveDirection moveDirection;
};
