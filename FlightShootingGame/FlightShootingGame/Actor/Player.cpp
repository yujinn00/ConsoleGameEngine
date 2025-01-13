#include "Player.h"
#include "Engine/Engine.h"
#include "Math/Vector2.h"
#include "PreCompiledHeader/PreCompiledHeader.h"

Player::Player(const char* image)
	: Super(image)
{
	// �÷��̾� ���� ��ġ
	position = Vector2(0, 18);
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

	// Ű �Է� ó��
	if (Engine::Get().GetKey(VK_RIGHT))
	{
		// �� ��ġ ���
		Vector2 newPosition = position;
		++newPosition.x;
		if (newPosition.x > 27)
		{
			newPosition.x = 27;
		}

		SetPosition(newPosition);
	}
}
