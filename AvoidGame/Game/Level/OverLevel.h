#pragma once

#include <Level/Level.h>

class OverLevel : public Level
{
	RTTI_DECLARATIONS(OverLevel, Level)

public:
	OverLevel();
	~OverLevel();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;
};
