#pragma once

#include <Actor/DrawableActor.h>

// ���� ���� ���� ����
class GameLevel;
class Player : public DrawableActor
{
	RTTI_DECLARATIONS(Player, DrawableActor)

public:
	Player(const Vector2& position, GameLevel* level);

	virtual void Update(float deltaTime) override;

private:
	// ���� ������ �����ϴ� ����
	GameLevel* refLevel = nullptr;
};
