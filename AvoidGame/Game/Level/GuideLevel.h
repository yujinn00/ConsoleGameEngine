#pragma once

#include <Level/Level.h>

class GuideLevel : public Level
{
	RTTI_DECLARATIONS(GuideLevel, Level)

public:
	GuideLevel();
	~GuideLevel();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;
};
