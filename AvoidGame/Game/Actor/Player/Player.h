#pragma once

#include "Actor/DrawableActor.h"

class Player : public DrawableActor
{
	RTTI_DECLARATIONS(Player, DrawableActor)

public:
	Player(const char* image = "p");

	virtual void Update(float deltaTime);

	// 탄약 발사 함수
	void Shoot();

	// 쉴드 생성 함수
	void CreateShield();

	// 쉴드 파괴 함수
	void DestroyShield();

	// 탄알 발사 쿨타임 감소 함수
	void DecreseCooldown();

	// 탄알 발사 쿨타임 반환 함수
	float GetCooldown() const;

public:
	// 현재 보호막 상태
	bool isShield = false;

private:
	// 플레이어 위치
	float preciseX = 0.0f;
	float preciseY = 0.0f;

	// X축 이동 속도 (초당 픽셀)
	float moveSpeedX = 20.0f;

	// Y축 이동 속도 (초당 픽셀)
	float moveSpeedY = 15.0f;

	// 탄알 스폰 타이머
	float spawnElapsedTimeBullet = 0.0f;
	float spawnIntervalBullet = 2.0f;
	bool isSpawnBullet = true;

	// 현재 바라보는 방향
	MoveDirection moveDirection = MoveDirection::Up;
};
