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
	float xPosition;
	float yPosition;

	// �̵� �ӵ�
	float speed;
};
