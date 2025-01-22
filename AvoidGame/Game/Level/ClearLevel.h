#pragma once

#include <Level/Level.h>

class ClearLevel : public Level
{
	RTTI_DECLARATIONS(ClearLevel, Level)

public:
	ClearLevel();
	~ClearLevel();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;
};
