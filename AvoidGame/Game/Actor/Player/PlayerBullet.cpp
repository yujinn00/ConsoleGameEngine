#include "PlayerBullet.h"
#include "Engine/Engine.h"

PlayerBullet::PlayerBullet(const Vector2& position, MoveDirection moveDirection, float speed)
	: DrawableActor("+"), moveDirection(moveDirection), speed(speed)
{
	// 색상 설정
	color = Color::White2;

	// 좌표 설정
	this->position = position;
	xPosition = (float)position.x;
	yPosition = (float)position.y;
}

void PlayerBullet::Update(float deltaTime)
{
	Super::Update(deltaTime);

	// 방향에 따라 총알 이동
	switch (moveDirection)
	{
	case MoveDirection::Up:
		yPosition -= speed * deltaTime;
		break;
	case MoveDirection::Down:
		yPosition += speed * deltaTime;
		break;
	case MoveDirection::Left:
		xPosition -= speed * deltaTime;
		break;
	case MoveDirection::Right:
		xPosition += speed * deltaTime;
		break;
	}

	// 위치 업데이트
	position.x = (int)xPosition;
	position.y = (int)yPosition;

	// 화면을 벗어나면 제거
	Vector2 screenSize = Engine::Get().ScreenSize();
	if (position.x < 1 || position.x >= screenSize.x - 1 || position.y < 1 || position.y >= screenSize.y - 1)
	{
		Destroy();
	}
}
