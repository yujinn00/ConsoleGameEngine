#include "PlayerBullet.h"

PlayerBullet::PlayerBullet(const Vector2& position)
	: DrawableActor("!")
{
	// 탄약 위치 설정
	this->position = position;
	yPosition = (float)position.y;
}

void PlayerBullet::Update(float deltaTime)
{
	Super::Update(deltaTime);

	// 위치 갱신
	// 프레임 시간을 고려한 이동
	yPosition -= speed * deltaTime;
	position.y = (int)yPosition;

	// y 좌표가 화면을 벗어나면 액터 삭제
	if (yPosition < 0.0f)
	{
		Destroy();
		return;
	}
}
