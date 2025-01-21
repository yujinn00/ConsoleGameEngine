#include "EnemyC.h"
#include "Engine/Engine.h"
#include "Level/GameLevel.h"
#include "Actor/Player.h"

#include <cmath>

EnemyC::EnemyC(const char* image, float speed)
    : DrawableActor(image), speed(speed)
{
    // ���� ����
    color = Color::Magenta;

    // �������� ���� ��ġ�� ����
    int randomStart = Random(0, 3); // 0: ��, 1: ��, 2: ��, 3: ��
    Vector2 screenSize = Engine::Get().ScreenSize();

    switch (randomStart)
    {
    case 0: // ��� ����
        xPosition = static_cast<float>(Random(1, screenSize.x - width - 1));
        yPosition = 1.0f;
        break;
    case 1: // �ϴ� ����
        xPosition = static_cast<float>(Random(1, screenSize.x - width - 1));
        yPosition = static_cast<float>(screenSize.y - width);
        break;
    case 2: // ���� ����
        xPosition = 1.0f;
        yPosition = static_cast<float>(Random(1, screenSize.y - width - 1));
        break;
    case 3: // ���� ����
        xPosition = static_cast<float>(screenSize.x - width);
        yPosition = static_cast<float>(Random(1, screenSize.y - width - 1));
        break;
    }

    // �ʱ� ��ġ ����
    SetPosition(Vector2(xPosition, yPosition));
}

void EnemyC::Update(float deltaTime)
{
    Super::Update(deltaTime);

    // ���� ���� ��������
    GameLevel* gameLevel = Engine::Get().GetCurrentLevel()->As<GameLevel>();

    // �÷��̾� ��������
    Player* player = gameLevel->GetPlayer();

    // �÷��̾� ��ġ ��������
    Vector2 playerPosition = player->GetPosition();

    // �÷��̾���� ���� ���� ���
    float dx = playerPosition.x - xPosition;
    float dy = playerPosition.y - yPosition;

    // �Ÿ� ���
    float distance = sqrt(dx * dx + dy * dy);

    // �Ÿ��� 0���� Ŭ ���� ���� ���
    if (distance > 0)
    {
        // ���� ���� ����ȭ
        dx /= distance;
        dy /= distance;

        // �ӵ��� �����Ͽ� �̵�
        xPosition += dx * speed * deltaTime;
        yPosition += dy * speed * deltaTime;

        // ��ġ�� ������ ��ȯ�Ͽ� ������Ʈ
        position.x = static_cast<int>(xPosition);
        position.y = static_cast<int>(yPosition);
    }
}
