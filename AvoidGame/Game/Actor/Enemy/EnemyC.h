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
	float xPosition;
	float yPosition;

	// ÀÌµ¿ ¼Óµµ
	float speed;
};
