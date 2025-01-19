#include "EnemyA.h"
#include "Engine/Engine.h"

#include <cstdlib>

EnemyA::EnemyA(const char* image, float speed)
	: DrawableActor(image), speed(speed), moveDirection(MoveDirection::Up)
{
	// ���� ����
	color = Color::Red;

	// �������� ���� ��ġ�� ������ ����
	int randomStart = Random(0, 3); // 0: ��, 1: ��, 2: ��, 3: ��
	Vector2 screenSize = Engine::Get().ScreenSize();

	switch (randomStart)
	{
	case 0: // ��� -> �ϴ�
		xPosition = static_cast<float>(Random(2, screenSize.x - width - 2));
		yPosition = 1.0f;
		moveDirection = MoveDirection::Down;
		break;
	case 1: // �ϴ� -> ���
		xPosition = static_cast<float>(Random(2, screenSize.x - width - 2));
		yPosition = static_cast<float>(screenSize.y - width);
		moveDirection = MoveDirection::Up;
		break;
	case 2: // ���� -> ����
		xPosition = 1.0f;
		yPosition = static_cast<float>(Random(2, screenSize.y - width - 2));
		moveDirection = MoveDirection::Right;
		break;
	case 3: // ���� -> ����
		xPosition = static_cast<float>(screenSize.x - width);
		yPosition = static_cast<float>(Random(2, screenSize.y - width - 2));
		moveDirection = MoveDirection::Left;
		break;
	}

	// �ʱ� ��ġ ����
	this->position = Vector2((int)xPosition, (int)yPosition);
}

void EnemyA::Update(float deltaTime)
{
	Super::Update(deltaTime);

	// �̵� ���⿡ ���� ��ǥ ����
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

	// ȭ�� ������ ������ ����
	Vector2 screenSize = Engine::Get().ScreenSize();
	if (position.y < 1 || position.y > screenSize.y - width - 1 || position.x < 1 || position.x > screenSize.x - width - 1)
	{
		Destroy();
	}
}
