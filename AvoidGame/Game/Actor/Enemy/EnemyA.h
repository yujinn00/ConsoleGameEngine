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
	float xPosition;
	float yPosition;

	// �̵� �ӵ�
	float speed;

	// �̵� ����
	MoveDirection moveDirection = MoveDirection::None;
};
