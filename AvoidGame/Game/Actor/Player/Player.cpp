#include "Player.h"
#include "PlayerBullet.h"
#include "Engine/Engine.h"
#include "Math/Vector2.h"

#include <cstring>

Player::Player(const char* image)
	: Super(image)
{
    // ���� ����
    color = Color::Cyan;

    // ȭ�� ũ�⸦ ������ �߾� ��ġ ���
    Vector2 screenSize = Engine::Get().ScreenSize();
    preciseX = static_cast<float>(screenSize.x / 2);
    preciseY = static_cast<float>(screenSize.y / 2);

    // �÷��̾� ��ġ ����
    SetPosition(Vector2(static_cast<int>(preciseX), static_cast<int>(preciseY)));
}

void Player::Update(float deltaTime)
{
    // �θ� �Լ� ȣ��
    Super::Update(deltaTime);

    // ��ũ�� ������ ��������
    Vector2 screenSize = Engine::Get().ScreenSize();

    // ��� Ű �Է� ó��
    if (Engine::Get().GetKey(VK_UP))
    {
        moveDirection = MoveDirection::Up;
        preciseY -= moveSpeedY * deltaTime;
        if (preciseY < 1.0f)
        {
            preciseY = 1.0f;
        }
    }

    // �ϴ� Ű �Է� ó��
    if (Engine::Get().GetKey(VK_DOWN))
    {
        moveDirection = MoveDirection::Down;
        preciseY += moveSpeedY * deltaTime;
        if (preciseY > screenSize.y - width - 1)
        {
            preciseY = static_cast<float>(screenSize.y - width - 1);
        }
    }

    // ���� Ű �Է� ó��
    if (Engine::Get().GetKey(VK_LEFT))
    {
        moveDirection = MoveDirection::Left;
        preciseX -= moveSpeedX * deltaTime;
        if (preciseX < 1.0f)
        {
            preciseX = 1.0f;
        }
    }

    // ���� Ű �Է� ó��
    if (Engine::Get().GetKey(VK_RIGHT))
    {
        moveDirection = MoveDirection::Right;
        preciseX += moveSpeedX * deltaTime;
        if (preciseX > screenSize.x - width - 1)
        {
            preciseX = static_cast<float>(screenSize.x - width - 1);
        }
    }

	// �Ѿ� �߻�
	if (isSpawnBullet)
	{
		Shoot();
		isSpawnBullet = false; // �Ѿ� �߻� �� �ٽ� ��Ÿ������ ����
	}

	// �Ѿ� �߻� Ÿ�̸� ������Ʈ
	spawnElapsedTimeBullet += deltaTime;
	if (spawnElapsedTimeBullet >= spawnIntervalBullet)
	{
		isSpawnBullet = true; // ��Ÿ���� ������ �ٽ� �߻� ����
		spawnElapsedTimeBullet = 0.0f;
	}

    // float���� int�� ��ȯ�Ͽ� ���� ��ġ ����
    position.x = static_cast<int>(preciseX);
    position.y = static_cast<int>(preciseY);

    SetPosition(position);
}

void Player::Shoot()
{
	// �Ѿ��� �ʱ� ��ġ�� �÷��̾��� ���� ��ġ
	Vector2 startPosition = position;

	// ���� ���⿡ ���� �Ѿ��� �ʱ� ��ġ ����
	switch (moveDirection)
	{
	case MoveDirection::Up:
		startPosition.y -= 1; // �÷��̾� ����
		break;
	case MoveDirection::Down:
		startPosition.y += 1; // �÷��̾� �Ʒ���
		break;
	case MoveDirection::Left:
		startPosition.x -= 1; // �÷��̾� ����
		break;
	case MoveDirection::Right:
		startPosition.x += 1; // �÷��̾� ������
		break;
	}

	// �Ѿ� ����
	Engine::Get().AddActor(new PlayerBullet(startPosition, moveDirection));
}

void Player::CreateShield()
{
    isShield = true;
    size_t length = strlen(image) + 1;
    strcpy_s(image, length, "P");
    color = Color::Blue;
}

void Player::DestroyShield()
{
    isShield = false;
    size_t length = strlen(image) + 1;
    strcpy_s(image, length, "p");
    color = Color::Cyan;
}

void Player::DecreseCooldown()
{
    spawnIntervalBullet -= 0.5f;
}

float Player::GetCooldown() const
{
    return spawnIntervalBullet - spawnElapsedTimeBullet;
}
