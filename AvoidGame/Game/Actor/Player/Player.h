#pragma once

#include "Actor/DrawableActor.h"

class Player : public DrawableActor
{
	RTTI_DECLARATIONS(Player, DrawableActor)

public:
	Player(const char* image = "p");

	virtual void Update(float deltaTime);

	// ź�� �߻� �Լ�
	void Shoot();

	// ���� ���� �Լ�
	void CreateShield();

	// ���� �ı� �Լ�
	void DestroyShield();

	// ź�� �߻� ��Ÿ�� ���� �Լ�
	void DecreseCooldown();

	// ź�� �߻� ��Ÿ�� ��ȯ �Լ�
	float GetCooldown() const;

public:
	// ���� ��ȣ�� ����
	bool isShield = false;

private:
	// �÷��̾� ��ġ
	float preciseX = 0.0f;
	float preciseY = 0.0f;

	// X�� �̵� �ӵ� (�ʴ� �ȼ�)
	float moveSpeedX = 20.0f;

	// Y�� �̵� �ӵ� (�ʴ� �ȼ�)
	float moveSpeedY = 15.0f;

	// ź�� ���� Ÿ�̸�
	float spawnElapsedTimeBullet = 0.0f;
	float spawnIntervalBullet = 2.0f;
	bool isSpawnBullet = true;

	// ���� �ٶ󺸴� ����
	MoveDirection moveDirection = MoveDirection::Up;
};
