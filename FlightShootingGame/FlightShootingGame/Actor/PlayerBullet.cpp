#include "PlayerBullet.h"

PlayerBullet::PlayerBullet(const Vector2& position)
	: DrawableActor("!")
{
	// ź�� ��ġ ����
	this->position = position;
	yPosition = (float)position.y;
}

void PlayerBullet::Update(float deltaTime)
{
	Super::Update(deltaTime);

	// ��ġ ����
	// ������ �ð��� ����� �̵�
	yPosition -= speed * deltaTime;
	position.y = (int)yPosition;

	// y ��ǥ�� ȭ���� ����� ���� ����
	if (yPosition < 0.0f)
	{
		Destroy();
		return;
	}
}
