#include "Enemy.h"
#include "Engine/Engine.h"

#include <cstdlib>

Enemy::Enemy(const char* image, float speed)
	: DrawableActor(image), speed(speed)
{
	// 랜덤으로 시작 위치와 방향을 결정
	int randomStart = Random(0, 3); // 0: 상, 1: 하, 2: 좌, 3: 우
	Vector2 screenSize = Engine::Get().ScreenSize();

	switch (randomStart)
	{
	case 0: // 상단 -> 하단
		xPosition = Random(1, screenSize.x - width);
		yPosition = 0.0f;
		direction = Direction::Down;
		break;
	case 1: // 하단 -> 상단
		xPosition = Random(1, screenSize.x - width);
		yPosition = screenSize.y - 1;
		direction = Direction::Up;
		break;
	case 2: // 좌측 -> 우측
		xPosition = 0.0f;
		yPosition = Random(1, screenSize.y - 1);
		direction = Direction::Right;
		break;
	case 3: // 우측 -> 좌측
		xPosition = screenSize.x - width;
		yPosition = Random(1, screenSize.y - 1);
		direction = Direction::Left;
		break;
	}

	// 초기 위치 설정
	this->position = Vector2((int)xPosition, (int)yPosition);
}

void Enemy::Update(float deltaTime)
{
	Super::Update(deltaTime);

	// 이동 방향에 따라 좌표 변경
	switch (direction)
	{
	case Direction::Down:
		yPosition += speed * deltaTime;
		position.y = (int)yPosition;
		break;
	case Direction::Up:
		yPosition -= speed * deltaTime;
		position.y = (int)yPosition;
		break;
	case Direction::Right:
		xPosition += speed * deltaTime;
		position.x = (int)xPosition;
		break;
	case Direction::Left:
		xPosition -= speed * deltaTime;
		position.x = (int)xPosition;
		break;
	}

	// 화면 밖으로 나가면 제거
	Vector2 screenSize = Engine::Get().ScreenSize();
	if (position.y < 0 || position.y > screenSize.y - 1 || position.x < 0 || position.x > screenSize.x - width)
	{
		Destroy();
	}
}
