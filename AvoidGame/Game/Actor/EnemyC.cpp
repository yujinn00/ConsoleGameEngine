#include "EnemyC.h"
#include "Engine/Engine.h"
#include "Level/GameLevel.h"
#include "Actor/Player.h"

#include <cmath>

EnemyC::EnemyC(const char* image, float speed)
    : DrawableActor(image), speed(speed)
{
    // 색상 설정
    color = Color::Magenta;

    // 랜덤으로 시작 위치를 결정
    int randomStart = Random(0, 3); // 0: 상, 1: 하, 2: 좌, 3: 우
    Vector2 screenSize = Engine::Get().ScreenSize();

    switch (randomStart)
    {
    case 0: // 상단 생성
        xPosition = static_cast<float>(Random(1, screenSize.x - width - 1));
        yPosition = 1.0f;
        break;
    case 1: // 하단 생성
        xPosition = static_cast<float>(Random(1, screenSize.x - width - 1));
        yPosition = static_cast<float>(screenSize.y - width);
        break;
    case 2: // 좌측 생성
        xPosition = 1.0f;
        yPosition = static_cast<float>(Random(1, screenSize.y - width - 1));
        break;
    case 3: // 우측 생성
        xPosition = static_cast<float>(screenSize.x - width);
        yPosition = static_cast<float>(Random(1, screenSize.y - width - 1));
        break;
    }

    // 초기 위치 설정
    SetPosition(Vector2(xPosition, yPosition));
}

void EnemyC::Update(float deltaTime)
{
    Super::Update(deltaTime);

    // 현재 레벨 가져오기
    GameLevel* gameLevel = Engine::Get().GetCurrentLevel()->As<GameLevel>();

    // 플레이어 가져오기
    Player* player = gameLevel->GetPlayer();

    // 플레이어 위치 가져오기
    Vector2 playerPosition = player->GetPosition();

    // 플레이어와의 방향 벡터 계산
    float dx = playerPosition.x - xPosition;
    float dy = playerPosition.y - yPosition;

    // 거리 계산
    float distance = sqrt(dx * dx + dy * dy);

    // 거리가 0보다 클 때만 방향 계산
    if (distance > 0)
    {
        // 방향 벡터 정규화
        dx /= distance;
        dy /= distance;

        // 속도를 적용하여 이동
        xPosition += dx * speed * deltaTime;
        yPosition += dy * speed * deltaTime;

        // 위치를 정수로 변환하여 업데이트
        position.x = static_cast<int>(xPosition);
        position.y = static_cast<int>(yPosition);
    }
}
