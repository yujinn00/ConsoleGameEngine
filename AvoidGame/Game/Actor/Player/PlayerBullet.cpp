#include "PlayerBullet.h"
#include "Engine/Engine.h"

PlayerBullet::PlayerBullet(const Vector2& position, MoveDirection moveDirection, float speed)
	: DrawableActor("+"), moveDirection(moveDirection), speed(speed)
{
	// ���� ����
	color = Color::White2;

	// ��ǥ ����
	this->position = position;
	xPosition = (float)position.x;
	yPosition = (float)position.y;
}

void PlayerBullet::Update(float deltaTime)
{
	Super::Update(deltaTime);

	// ���⿡ ���� �Ѿ� �̵�
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

	// ��ġ ������Ʈ
	position.x = (int)xPosition;
	position.y = (int)yPosition;

	// ȭ���� ����� ����
	Vector2 screenSize = Engine::Get().ScreenSize();
	if (position.x < 1 || position.x >= screenSize.x - 1 || position.y < 1 || position.y >= screenSize.y - 1)
	{
		Destroy();
	}
}
