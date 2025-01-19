#include "EnemyA.h"
#include "Engine/Engine.h"

#include <cstdlib>

EnemyA::EnemyA(const char* image, float speed)
	: DrawableActor(image), speed(speed), moveDirection(MoveDirection::Up)
{
	// 색상 설정
	color = Color::Red;

	// 랜덤으로 시작 위치와 방향을 결정
	int randomStart = Random(0, 3); // 0: 상, 1: 하, 2: 좌, 3: 우
	Vector2 screenSize = Engine::Get().ScreenSize();

	switch (randomStart)
	{
	case 0: // 상단 -> 하단
		xPosition = static_cast<float>(Random(2, screenSize.x - width - 2));
		yPosition = 1.0f;
		moveDirection = MoveDirection::Down;
		break;
	case 1: // 하단 -> 상단
		xPosition = static_cast<float>(Random(2, screenSize.x - width - 2));
		yPosition = static_cast<float>(screenSize.y - width);
		moveDirection = MoveDirection::Up;
		break;
	case 2: // 좌측 -> 우측
		xPosition = 1.0f;
		yPosition = static_cast<float>(Random(2, screenSize.y - width - 2));
		moveDirection = MoveDirection::Right;
		break;
	case 3: // 우측 -> 좌측
		xPosition = static_cast<float>(screenSize.x - width);
		yPosition = static_cast<float>(Random(2, screenSize.y - width - 2));
		moveDirection = MoveDirection::Left;
		break;
	}

	// 초기 위치 설정
	this->position = Vector2((int)xPosition, (int)yPosition);
}

void EnemyA::Update(float deltaTime)
{
	Super::Update(deltaTime);

	// 이동 방향에 따라 좌표 변경
	switch (moveDirection)
	{
	case MoveDirection::Down:
		yPosition += speed * deltaTime;
		position.y = (int)yPosition;
		break;
	case MoveDirection::Up:
		yPosition -= speed * deltaTime;
		position.y = (int)yPosition;
		break;
	case MoveDirection::Right:
		xPosition += speed * deltaTime;
		position.x = (int)xPosition;
		break;
	case MoveDirection::Left:
		xPosition -= speed * deltaTime;
		position.x = (int)xPosition;
		break;
	}

	// 화면 밖으로 나가면 제거
	Vector2 screenSize = Engine::Get().ScreenSize();
	if (position.y < 1 || position.y > screenSize.y - width - 1 || position.x < 1 || position.x > screenSize.x - width - 1)
	{
		Destroy();
	}
}
