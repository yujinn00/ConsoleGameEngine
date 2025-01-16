#include "Player.h"
#include "Engine/Engine.h"
#include "Game/Game.h"
#include "Level/GameLevel.h"

Player::Player(const Vector2& position, GameLevel* level)
	: DrawableActor("P"), refLevel(level)
{
	// 위치 설정
	this->position = position;

	// 색상 설정
	color = Color::White;
}

void Player::Update(float deltaTime)
{
	Super::Update(deltaTime);

	// ESC 토글 메뉴
	if (Engine::Get().GetKeyDown(VK_ESCAPE))
	{
		Game::Get().ToggleMenu();
	}

	// 좌로 이동
	if (Engine::Get().GetKeyDown(VK_LEFT))
	{
		// 이동 가능한지 확인
		if (refLevel->canPlayerMove(Vector2(position.x - 1, position.y)))
		{
			position.x -= 1;
		}
	}

	// 우로 이동
	if (Engine::Get().GetKeyDown(VK_RIGHT))
	{
		// 이동 가능한지 확인
		if (refLevel->canPlayerMove(Vector2(position.x + 1, position.y)))
		{
			position.x += 1;
		}
	}

	// 위로 이동
	if (Engine::Get().GetKeyDown(VK_UP))
	{
		// 이동 가능한지 확인
		if (refLevel->canPlayerMove(Vector2(position.x, position.y - 1)))
		{
			position.y -= 1;
		}
	}

	// 아래로 이동
	if (Engine::Get().GetKeyDown(VK_DOWN))
	{
		// 이동 가능한지 확인
		if (refLevel->canPlayerMove(Vector2(position.x, position.y + 1)))
		{
			position.y += 1;
		}
	}
}
