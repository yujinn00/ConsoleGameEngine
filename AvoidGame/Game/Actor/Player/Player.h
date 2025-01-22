#pragma once

#include "Actor/DrawableActor.h"

class Player : public DrawableActor
{
	RTTI_DECLARATIONS(Player, DrawableActor)

public:
	Player(const char* image = "P");

	virtual void Update(float deltaTime);

	// ź�� �߻� �Լ�
	void Shoot();

	// ���� ���� �Լ�
	void CreateShield();

	// ���� �ı� �Լ�
	void DestroyShield();

	// �Ѿ� �߻� ��Ÿ�� ����
	void DecreseCooldown();

public:
	// ���� ��ȣ�� ����
	bool isShield = false;

private:
	// x�� �̵� �ӵ� (�ʴ� �ȼ�)
	float moveSpeedX = 20.0f;

	// y�� �̵� �ӵ� (�ʴ� �ȼ�)
	float moveSpeedY = 15.0f;

	// ź�� ���� Ÿ�̸�
	float spawnElapsedTimeBullet = 0.0f;
	float spawnIntervalBullet = 2.0f;
	bool isSpawnBullet = true;

	// ���� �ٶ󺸴� ����
	MoveDirection moveDirection = MoveDirection::Up;
};
