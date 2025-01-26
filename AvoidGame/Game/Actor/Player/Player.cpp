#include "Player.h"
#include "PlayerBullet.h"
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

    // 상단 키 입력 처리
    if (Engine::Get().GetKey(VK_UP))
    {
        moveDirection = MoveDirection::Up;
        preciseY -= moveSpeedY * deltaTime;
        if (preciseY < 1.0f)
        {
            preciseY = 1.0f;
        }
    }

    // 하단 키 입력 처리
    if (Engine::Get().GetKey(VK_DOWN))
    {
        moveDirection = MoveDirection::Down;
        preciseY += moveSpeedY * deltaTime;
        if (preciseY > screenSize.y - width - 1)
        {
            preciseY = static_cast<float>(screenSize.y - width - 1);
        }
    }

    // 좌측 키 입력 처리
    if (Engine::Get().GetKey(VK_LEFT))
    {
        moveDirection = MoveDirection::Left;
        preciseX -= moveSpeedX * deltaTime;
        if (preciseX < 1.0f)
        {
            preciseX = 1.0f;
        }
    }

    // 우측 키 입력 처리
    if (Engine::Get().GetKey(VK_RIGHT))
    {
        moveDirection = MoveDirection::Right;
        preciseX += moveSpeedX * deltaTime;
        if (preciseX > screenSize.x - width - 1)
        {
            preciseX = static_cast<float>(screenSize.x - width - 1);
        }
    }

    // 총알 발사
    if (isSpawnBullet)
    {
        Shoot();
        isSpawnBullet = false; // 총알 발사 후 다시 쿨타임으로 진입
    }

    // 총알 발사 타이머 업데이트
    spawnElapsedTimeBullet += deltaTime;
    if (spawnElapsedTimeBullet >= spawnIntervalBullet)
    {
        isSpawnBullet = true; // 쿨타임이 지나면 다시 발사 가능
        spawnElapsedTimeBullet = 0.0f;
    }

    // float에서 int로 변환하여 최종 위치 적용
    position.x = static_cast<int>(preciseX);
    position.y = static_cast<int>(preciseY);

    SetPosition(position);
}

void Player::Shoot()
{
	// 총알의 초기 위치는 플레이어의 현재 위치
	Vector2 startPosition = position;

	// 현재 방향에 따라 총알의 초기 위치 조정
	switch (moveDirection)
	{
	case MoveDirection::Up:
		startPosition.y -= 1; // 플레이어 위쪽
		break;
	case MoveDirection::Down:
		startPosition.y += 1; // 플레이어 아래쪽
		break;
	case MoveDirection::Left:
		startPosition.x -= 1; // 플레이어 왼쪽
		break;
	case MoveDirection::Right:
		startPosition.x += 1; // 플레이어 오른쪽
		break;
	}

	// 총알 생성
	Engine::Get().AddActor(new PlayerBullet(startPosition, moveDirection));
}

void Player::CreateShield()
{
    isShield = true;
    color = Color::Blue;
}

void Player::DestroyShield()
{
    isShield = false;
    color = Color::Cyan;
}

void Player::DecreseCooldown()
{
    spawnIntervalBullet -= 0.5f;
}
