#include "Player.h"
#include "Engine/Engine.h"
#include "Math/Vector2.h"

Player::Player(char image)
	: Super(image)
{
}

void Player::Update(float deltaTime)
{
	// �θ� �Լ� ȣ��
	Super::Update(deltaTime);

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

	if (Engine::Get().GetKey(VK_RIGHT))
	{
		// �� ��ġ ���
		Vector2 newPosition = position;
		++newPosition.x;
		if (newPosition.x > 40)
		{
			newPosition.x = 40;
		}

		SetPosition(newPosition);
	}
}
