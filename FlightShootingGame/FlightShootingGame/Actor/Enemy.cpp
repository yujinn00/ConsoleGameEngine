#include "Enemy.h"
#include <Engine/Engine.h>
#include "Actor/EnemyBullet.h"

Enemy::Enemy(const char* image, int yPosition)
	: DrawableActor(image)
{
	// �������� �̵��� ���� ����
	int random = Random(1, 10);
	if (random % 2 == 0)
	{
		// ¦���� ��쿡�� �������� �̵��ϵ��� ����
		direction = Direction::Left;

		// x ��ǥ�� ȭ�� ������ ����
		xPosition = (float)(Engine::Get().ScreenSize().x - width);
	}
	else
	{
		// Ȧ���� ��쿡�� ���������� �̵��ϵ��� ����
		direction = Direction::Right;

		// x ��ǥ�� 0���� ����
		xPosition = 0.0f;
	}

	// ���� ��ġ ����
	this->position = Vector2((int)xPosition, yPosition);
}

void Enemy::Update(float deltaTime)
{
	Super::Update(deltaTime);

	// �¿� �̵�
	float factor = direction == Direction::Left ? -1.0f : 1.0f;
	xPosition += speed * factor * deltaTime;
	position.x = (int)xPosition;

	// ȭ�� ������ ����� ����
	if (xPosition < 0.0f || position.x > Engine::Get().ScreenSize().x - width)
	{
		Destroy();
	}

	// ź�� �߻�
	static float elapsedTime = 0.0f;
	static float fireInterval = RandomPercent(1.0f, 2.0f);

	// Ÿ�̸� ������Ʈ
	elapsedTime += deltaTime;

	// Ÿ�̸� ó��
	if (elapsedTime < fireInterval)
	{
		return;
	}

	// Ÿ�̸� �ʱ�ȭ
	elapsedTime = 0.0f;
	fireInterval = RandomPercent(1.0f, 2.0f);

	// ź�� ����
	Engine::Get().AddActor(
		new EnemyBullet(Vector2(position.x + width / 2, position.y))
	);
}
