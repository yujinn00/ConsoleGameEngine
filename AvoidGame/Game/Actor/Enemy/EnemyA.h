#pragma once

#include "Actor/DrawableActor.h"

class EnemyA : public DrawableActor
{
	RTTI_DECLARATIONS(EnemyA, DrawableActor)

public:
	EnemyA(const char* image, float speed);

	virtual void Update(float deltaTime) override;

private:
	// x ��ǥ �� y ��ǥ
	float xPosition = 0.0f;
	float yPosition = 0.0f;

	// �̵� �ӵ�
	float speed = 0.0f;

	// �̵� ����
	MoveDirection moveDirection;
};
