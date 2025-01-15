#include "EnemyBullet.h"
#include "Engine/Engine.h"

EnemyBullet::EnemyBullet(const Vector2& position)
	: DrawableActor("o")
{
	// ��ġ ����
	this->position = position;
	yPosition = (float)position.y;
}

void EnemyBullet::Update(float deltaTime)
{
	Super::Update(deltaTime);

	// �̵� ����
	yPosition += speed * deltaTime;
	position.y = (int)yPosition;

	// ȭ�� ����� ����
	if (yPosition >= Engine::Get().ScreenSize().y)
	{
		Destroy();
	}
}
