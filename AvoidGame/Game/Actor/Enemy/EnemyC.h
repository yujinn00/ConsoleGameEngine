#pragma once

#include "Actor/DrawableActor.h"

class EnemyC : public DrawableActor
{
	RTTI_DECLARATIONS(EnemyC, DrawableActor)

public:
	EnemyC(const char* image, float speed);

	virtual void Update(float deltaTime) override;

private:
	// x ��ǥ �� y ��ǥ
	float xPosition = 0.0f;
	float yPosition = 0.0f;

	// �̵� �ӵ�
	float speed = 0.0f;
};
