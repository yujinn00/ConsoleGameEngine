#pragma once

#include "Actor/DrawableActor.h"

class Player : public DrawableActor
{
	RTTI_DECLARATIONS(Player, DrawableActor)

public:
	Player(const char* image = "P");

	virtual void Update(float deltaTime);

	// 탄약 발사 함수
	void Shoot();

	// 쉴드 생성 함수
	void CreateShield();

	// 쉴드 파괴 함수
	void DestroyShield();

public:
	// 현재 보호막 상태
	bool isShield = false;

private:
	// x축 이동 속도 (초당 픽셀)
	float moveSpeedX = 20.0f;

	// y축 이동 속도 (초당 픽셀)
	float moveSpeedY = 15.0f;

	// 현재 바라보는 방향
	MoveDirection moveDirection;
};
