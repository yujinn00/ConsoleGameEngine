#include "Player.h"
#include "Engine/Engine.h"
#include "Math/Vector2.h"
#include "Actor/PlayerBullet.h"

Player::Player(const char* image)
	: Super(image)
{
	// �÷��̾� ���� ��ġ
	position = Vector2(0, 20);
}

void Player::Update(float deltaTime)
{
	// �θ� �Լ� ȣ��
	Super::Update(deltaTime);

	// ź�� �߻�
	if (Engine::Get().GetKeyDown(VK_SPACE))
	{
		Vector2 bulletPosition(position.x + (width / 2), position.y);
		Engine::Get().AddActor(new PlayerBullet(bulletPosition));
	}

	// Ű �Է� ó��
	if (Engine::Get().GetKey(VK_LEFT))
	{
		// �� ��ġ ���
		Vector2 newPosition = position;
		--newPosition.x;
		if (newPosition.x < 0)
		{
			newPosition.x = 0;
		}

		SetPosition(newPosition);
	}

	// Ű �Է� ó��
	if (Engine::Get().GetKey(VK_RIGHT))
	{
		// �� ��ġ ���
		Vector2 newPosition = position;
		++newPosition.x;
		if (newPosition.x > Engine::Get().ScreenSize().x - width)
		{
			newPosition.x = Engine::Get().ScreenSize().x - width;
		}

		SetPosition(newPosition);
	}
}
