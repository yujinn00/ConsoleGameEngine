#include "EnemyB.h"
#include "EnemyBullet.h"
#include "Engine/Engine.h"

#include <cstdlib>

EnemyB::EnemyB(const char* image, SpawnPosition spawnPosition, float speed)
    : DrawableActor(image), spawnPosition(spawnPosition), speed(speed)
{
    // 색상 설정
    color = Color::Yellow;

    Vector2 screenSize = Engine::Get().ScreenSize();

    // 랜덤으로 시작 위치와 이동 방향 설정
    switch (spawnPosition)
    {
    case SpawnPosition::Top: // 상단 -> 좌우 이동
        xPosition = static_cast<float>(Random(3, screenSize.x - width - 2));
        yPosition = 1.0f;
        moveDirection = (Random(0, 1) == 0) ? MoveDirection::Left : MoveDirection::Right;
        break;

    case SpawnPosition::Bottom: // 하단 -> 좌우 이동
        xPosition = static_cast<float>(Random(3, screenSize.x - width - 2));
        yPosition = static_cast<float>(screenSize.y - width - 1);
        moveDirection = (Random(0, 1) == 0) ? MoveDirection::Left : MoveDirection::Right;
        break;

    case SpawnPosition::Left: // 좌측 -> 상하 이동
        xPosition = 1.0f;
        yPosition = static_cast<float>(Random(3, screenSize.y - width - 2));
        moveDirection = (Random(0, 1) == 0) ? MoveDirection::Up : MoveDirection::Down;
        break;

    case SpawnPosition::Right: // 우측 -> 상하 이동
        xPosition = static_cast<float>(screenSize.x - width - 1);
        yPosition = static_cast<float>(Random(3, screenSize.y - width - 2));
        moveDirection = (Random(0, 1) == 0) ? MoveDirection::Up : MoveDirection::Down;
        break;
    }

    // 초기 위치 설정
    SetPosition(Vector2(xPosition, yPosition));
}

void EnemyB::Update(float deltaTime)
{
    Super::Update(deltaTime);

    // 이동 방향에 따라 좌표 변경
    Vector2 screenSize = Engine::Get().ScreenSize();

    if (moveDirection == MoveDirection::Right || moveDirection == MoveDirection::Left)
    {
        // 좌우 이동
        xPosition += (moveDirection == MoveDirection::Right ? speed : -speed) * deltaTime;
        if (xPosition <= 2 || xPosition >= screenSize.x - width - 1) // 좌우 경계에서 방향 반전
        {
            speed = -speed; // 방향 반전
        }
        position.x = (int)xPosition;
    }
    else if (moveDirection == MoveDirection::Up || moveDirection == MoveDirection::Down)
    {
        // 상하 이동
        yPosition += (moveDirection == MoveDirection::Down ? speed : -speed) * deltaTime;
        if (yPosition <= 2 || yPosition >= screenSize.y - width - 1) // 상하 경계에서 방향 반전
        {
            speed = -speed; // 방향 반전
        }
        position.y = (int)yPosition;
    }

    // 총알 발사 로직
    static float fireElapsedTime = 0.0f;
    static float fireInterval = 1.0f; // 총알 발사 간격
    fireElapsedTime += deltaTime;

    if (fireElapsedTime >= fireInterval)
    {
        fireElapsedTime = 0.0f;
        fireInterval = RandomPercent(1.0f, 3.0f); // 다음 발사 간격 재설정

        // 총알 생성 위치 조정
        Vector2 bulletPosition = position;
        switch (spawnPosition)
        {
        case SpawnPosition::Top:
            bulletPosition.y += 1; // 한 칸 아래
            break;
        case SpawnPosition::Bottom:
            bulletPosition.y -= 1; // 한 칸 위
            break;
        case SpawnPosition::Left:
            bulletPosition.x += 1; // 한 칸 오른쪽
            break;
        case SpawnPosition::Right:
            bulletPosition.x -= 1; // 한 칸 왼쪽
            break;
        }

        // 총알 방향 설정
        MoveDirection bulletDirection{};
        switch (spawnPosition)
        {
        case SpawnPosition::Top: // 위쪽에서 생성된 경우
            bulletDirection = MoveDirection::Down; // 아래로 발사
            break;

        case SpawnPosition::Bottom: // 아래쪽에서 생성된 경우
            bulletDirection = MoveDirection::Up; // 위로 발사
            break;

        case SpawnPosition::Left: // 왼쪽에서 생성된 경우
            bulletDirection = MoveDirection::Right; // 오른쪽으로 발사
            break;

        case SpawnPosition::Right: // 오른쪽에서 생성된 경우
            bulletDirection = MoveDirection::Left; // 왼쪽으로 발사
            break;
        }

        // 총알 추가
        Engine::Get().AddActor(new EnemyBullet(position, bulletDirection));
    }
}
