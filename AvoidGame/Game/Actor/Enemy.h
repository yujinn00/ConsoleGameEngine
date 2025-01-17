#pragma once

#include "Actor/DrawableActor.h"

// ��ġ�� �̵� ����
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
	// x ��ǥ �� y ��ǥ ���
	float xPosition = 0.0f;
	float yPosition = 0.0f;

	// �̵� �ӵ�
	float speed = 0.0f;

	// �̵� ����
	Direction direction;
};
