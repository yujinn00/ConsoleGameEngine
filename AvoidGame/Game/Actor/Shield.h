#pragma once

#include "Actor/DrawableActor.h"

class Shield : public DrawableActor
{
	RTTI_DECLARATIONS(Shield, DrawableActor)

public:
	Shield(const char* image);

	virtual void Update(float deltaTime) override;
};
