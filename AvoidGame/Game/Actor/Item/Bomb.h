#pragma once

#include "Actor/DrawableActor.h"

class Bomb : public DrawableActor
{
	RTTI_DECLARATIONS(Bomb, DrawableActor)

public:
	Bomb(const char* image);

	virtual void Update(float deltaTime) override;
};
