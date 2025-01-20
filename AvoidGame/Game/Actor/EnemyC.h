#pragma once

#include "Actor/DrawableActor.h"

class EnemyC : public DrawableActor
{
	RTTI_DECLARATIONS(EnemyC, DrawableActor)

public:
	EnemyC(const char* image, float speed);

	virtual void Update(float deltaTime) override;

private:
	// x ÁÂÇ¥ ¹× y ÁÂÇ¥
	float xPosition = 0.0f;
	float yPosition = 0.0f;

	// ÀÌµ¿ ¼Óµµ
	float speed = 0.0f;
};
