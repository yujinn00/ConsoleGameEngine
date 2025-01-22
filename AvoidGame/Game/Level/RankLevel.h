#pragma once

#include <Level/Level.h>

class RankLevel : public Level
{
	RTTI_DECLARATIONS(RankLevel, Level)

public:
	RankLevel();
	~RankLevel();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

	void LoadScore();
};
