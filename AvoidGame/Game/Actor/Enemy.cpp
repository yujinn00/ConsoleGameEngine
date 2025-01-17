#include "Enemy.h"
#include "Engine/Engine.h"

#include <cstdlib>

Enemy::Enemy(const char* image, float speed)
	: DrawableActor(image), speed(speed)
{
	// �������� ���� ��ġ�� ������ ����
	int randomStart = Random(0, 3); // 0: ��, 1: ��, 2: ��, 3: ��
	Vector2 screenSize = Engine::Get().ScreenSize();

	switch (randomStart)
	{
	case 0: // ��� -> �ϴ�
		xPosition = Random(1, screenSize.x - width);
		yPosition = 0.0f;
		direction = Direction::Down;
		break;
	case 1: // �ϴ� -> ���
		xPosition = Random(1, screenSize.x - width);
		yPosition = screenSize.y - 1;
		direction = Direction::Up;
		break;
	case 2: // ���� -> ����
		xPosition = 0.0f;
		yPosition = Random(1, screenSize.y - 1);
		direction = Direction::Right;
		break;
	case 3: // ���� -> ����
		xPosition = screenSize.x - width;
		yPosition = Random(1, screenSize.y - 1);
		direction = Direction::Left;
		break;
	}

	// �ʱ� ��ġ ����
	this->position = Vector2((int)xPosition, (int)yPosition);
}

void Enemy::Update(float deltaTime)
{
	Super::Update(deltaTime);

	// �̵� ���⿡ ���� ��ǥ ����
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

	// ȭ�� ������ ������ ����
	Vector2 screenSize = Engine::Get().ScreenSize();
	if (position.y < 0 || position.y > screenSize.y - 1 || position.x < 0 || position.x > screenSize.x - width)
	{
		Destroy();
	}
}
