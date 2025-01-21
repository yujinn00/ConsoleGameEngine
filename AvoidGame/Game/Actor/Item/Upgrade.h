#pragma once

#include "Actor/DrawableActor.h"

class Upgrade : public DrawableActor
{
	RTTI_DECLARATIONS(Upgrade, DrawableActor)

public:
	Upgrade(const char* image);

	virtual void Update(float deltaTime) override;
};
