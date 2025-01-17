#pragma once

#include "Actor/DrawableActor.h"

class Player : public DrawableActor
{
	RTTI_DECLARATIONS(Player, DrawableActor)

public:
	Player(const char* image = "P");

	virtual void Update(float deltaTime);

private:
	// x축 이동 속도 (초당 픽셀)
	float moveSpeedX = 20.0f;

	// y축 이동 속도 (초당 픽셀)
	float moveSpeedY = 15.0f;
};
