#include "Player.h"
#include "Engine/Engine.h"
#include "Math/Vector2.h"

Player::Player(const char* image)
	: Super(image)
{
    // 색상 설정
    color = Color::Cyan;

	// 화면 크기를 가져와 중앙 위치 계산
	Vector2 screenSize = Engine::Get().ScreenSize();
	Vector2 centerPosition(screenSize.x / 2, screenSize.y / 2);

	// 플레이어 위치를 화면 중앙으로 설정
	SetPosition(centerPosition);
}

void Player::Update(float deltaTime)
{
    // 부모 함수 호출
    Super::Update(deltaTime);

    // 스크린 사이즈 가져오기
    Vector2 screenSize = Engine::Get().ScreenSize();

    // 현재 위치를 float로 변환
    static float preciseX = static_cast<float>(position.x);
    static float preciseY = static_cast<float>(position.y);

    // 하단 키 입력 처리
    if (Engine::Get().GetKey(VK_DOWN))
    {
        preciseY += moveSpeedY * deltaTime;
        if (preciseY > screenSize.y - width - 1)
        {
            preciseY = screenSize.y - width - 1;
        }
    }

    // 상단 키 입력 처리
    if (Engine::Get().GetKey(VK_UP))
    {
        preciseY -= moveSpeedY * deltaTime;
        if (preciseY < 1.0f)
        {
            preciseY = 1.0f;
        }
    }

    // 우측 키 입력 처리
    if (Engine::Get().GetKey(VK_RIGHT))
    {
        preciseX += moveSpeedX * deltaTime;
        if (preciseX > screenSize.x - width - 1)
        {
            preciseX = screenSize.x - width - 1;
        }
    }

    // 좌측 키 입력 처리
    if (Engine::Get().GetKey(VK_LEFT))
    {
        preciseX -= moveSpeedX * deltaTime;
        if (preciseX < 1.0f)
        {
            preciseX = 1.0f;
        }
    }

    // float에서 int로 변환하여 최종 위치 적용
    position.x = static_cast<int>(preciseX);
    position.y = static_cast<int>(preciseY);

    SetPosition(position);
}
