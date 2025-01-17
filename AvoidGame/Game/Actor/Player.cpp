#include "Player.h"
#include "Engine/Engine.h"
#include "Math/Vector2.h"

Player::Player(const char* image)
	: Super(image)
{
	// ȭ�� ũ�⸦ ������ �߾� ��ġ ���
	Vector2 screenSize = Engine::Get().ScreenSize();
	Vector2 centerPosition(screenSize.x / 2, screenSize.y / 2);

	// �÷��̾� ��ġ�� ȭ�� �߾����� ����
	SetPosition(centerPosition);
}

void Player::Update(float deltaTime)
{
    // �θ� �Լ� ȣ��
    Super::Update(deltaTime);

    // ��ũ�� ������ ��������
    Vector2 screenSize = Engine::Get().ScreenSize();

    // ���� ��ġ�� float�� ��ȯ
    static float preciseX = static_cast<float>(position.x);
    static float preciseY = static_cast<float>(position.y);

    // ��� Ű �Է� ó��
    if (Engine::Get().GetKey(VK_UP))
    {
        preciseY -= moveSpeedY * deltaTime;
        if (preciseY < 1.0f)
        {
            preciseY = 1.0f;
        }
    }

    // �ϴ� Ű �Է� ó��
    if (Engine::Get().GetKey(VK_DOWN))
    {
        preciseY += moveSpeedY * deltaTime;
        if (preciseY > screenSize.y - 2.0f)
        {
            preciseY = screenSize.y - 2.0f;
        }
    }

    // ���� Ű �Է� ó��
    if (Engine::Get().GetKey(VK_LEFT))
    {
        preciseX -= moveSpeedX * deltaTime;
        if (preciseX < 1.0f)
        {
            preciseX = 1.0f;
        }
    }

    // ���� Ű �Է� ó��
    if (Engine::Get().GetKey(VK_RIGHT))
    {
        preciseX += moveSpeedX * deltaTime;
        if (preciseX > screenSize.x - 2.0f)
        {
            preciseX = screenSize.x - 2.0f;
        }
    }

    // float���� int�� ��ȯ�Ͽ� ���� ��ġ ����
    position.x = static_cast<int>(preciseX);
    position.y = static_cast<int>(preciseY);

    SetPosition(position);
}
