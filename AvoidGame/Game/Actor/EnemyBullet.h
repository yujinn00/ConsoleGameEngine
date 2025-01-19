#pragma once

#include <Actor/DrawableActor.h>

class EnemyBullet : public DrawableActor
{
	RTTI_DECLARATIONS(EnemyBullet, DrawableActor)

public:
	EnemyBullet(const Vector2& position, MoveDirection moveDirection, float speed);

	virtual void Update(float deltaTime) override;

private:
	// x ��ǥ
	float xPosition = 0.0f;

	// y ��ǥ
	float yPosition = 0.0f;

	// �̵� �ӵ�
	float speed = 10.0f;

	// �̵� ����
	MoveDirection moveDirection;
};
