#include "EnemyB.h"
#include "EnemyBullet.h"
#include "Engine/Engine.h"

#include <cstdlib>

EnemyB::EnemyB(const char* image, SpawnPosition spawnPosition, float speed)
    : DrawableActor(image), spawnPosition(spawnPosition), speed(speed)
{
    // ���� ����
    color = Color::Yellow;

    Vector2 screenSize = Engine::Get().ScreenSize();

    // �������� ���� ��ġ�� �̵� ���� ����
    switch (spawnPosition)
    {
    case SpawnPosition::Top: // ��� -> �¿� �̵�
        xPosition = static_cast<float>(Random(3, screenSize.x - width - 2));
        yPosition = 1.0f;
        moveDirection = (Random(0, 1) == 0) ? MoveDirection::Left : MoveDirection::Right;
        break;

    case SpawnPosition::Bottom: // �ϴ� -> �¿� �̵�
        xPosition = static_cast<float>(Random(3, screenSize.x - width - 2));
        yPosition = static_cast<float>(screenSize.y - width - 1);
        moveDirection = (Random(0, 1) == 0) ? MoveDirection::Left : MoveDirection::Right;
        break;

    case SpawnPosition::Left: // ���� -> ���� �̵�
        xPosition = 1.0f;
        yPosition = static_cast<float>(Random(3, screenSize.y - width - 2));
        moveDirection = (Random(0, 1) == 0) ? MoveDirection::Up : MoveDirection::Down;
        break;

    case SpawnPosition::Right: // ���� -> ���� �̵�
        xPosition = static_cast<float>(screenSize.x - width - 1);
        yPosition = static_cast<float>(Random(3, screenSize.y - width - 2));
        moveDirection = (Random(0, 1) == 0) ? MoveDirection::Up : MoveDirection::Down;
        break;
    }

    // �ʱ� ��ġ ����
    SetPosition(Vector2(xPosition, yPosition));
}

void EnemyB::Update(float deltaTime)
{
    Super::Update(deltaTime);

    // �̵� ���⿡ ���� ��ǥ ����
    Vector2 screenSize = Engine::Get().ScreenSize();

    if (moveDirection == MoveDirection::Right || moveDirection == MoveDirection::Left)
    {
        // �¿� �̵�
        xPosition += (moveDirection == MoveDirection::Right ? speed : -speed) * deltaTime;
        if (xPosition <= 2 || xPosition >= screenSize.x - width - 1) // �¿� ��迡�� ���� ����
        {
            speed = -speed; // ���� ����
        }
        position.x = (int)xPosition;
    }
    else if (moveDirection == MoveDirection::Up || moveDirection == MoveDirection::Down)
    {
        // ���� �̵�
        yPosition += (moveDirection == MoveDirection::Down ? speed : -speed) * deltaTime;
        if (yPosition <= 2 || yPosition >= screenSize.y - width - 1) // ���� ��迡�� ���� ����
        {
            speed = -speed; // ���� ����
        }
        position.y = (int)yPosition;
    }

    // �Ѿ� �߻� ����
    static float fireElapsedTime = 0.0f;
    static float fireInterval = 1.0f; // �Ѿ� �߻� ����
    fireElapsedTime += deltaTime;

    if (fireElapsedTime >= fireInterval)
    {
        fireElapsedTime = 0.0f;
        fireInterval = RandomPercent(1.0f, 3.0f); // ���� �߻� ���� �缳��

        // �Ѿ� ���� ��ġ ����
        Vector2 bulletPosition = position;
        switch (spawnPosition)
        {
        case SpawnPosition::Top:
            bulletPosition.y += 1; // �� ĭ �Ʒ�
            break;
        case SpawnPosition::Bottom:
            bulletPosition.y -= 1; // �� ĭ ��
            break;
        case SpawnPosition::Left:
            bulletPosition.x += 1; // �� ĭ ������
            break;
        case SpawnPosition::Right:
            bulletPosition.x -= 1; // �� ĭ ����
            break;
        }

        // �Ѿ� ���� ����
        MoveDirection bulletDirection{};
        switch (spawnPosition)
        {
        case SpawnPosition::Top: // ���ʿ��� ������ ���
            bulletDirection = MoveDirection::Down; // �Ʒ��� �߻�
            break;

        case SpawnPosition::Bottom: // �Ʒ��ʿ��� ������ ���
            bulletDirection = MoveDirection::Up; // ���� �߻�
            break;

        case SpawnPosition::Left: // ���ʿ��� ������ ���
            bulletDirection = MoveDirection::Right; // ���������� �߻�
            break;

        case SpawnPosition::Right: // �����ʿ��� ������ ���
            bulletDirection = MoveDirection::Left; // �������� �߻�
            break;
        }

        // �Ѿ� �߰�
        Engine::Get().AddActor(new EnemyBullet(position, bulletDirection));
    }
}
