#pragma once

#include "Actor/DrawableActor.h"

class EnemyB : public DrawableActor
{
	RTTI_DECLARATIONS(EnemyB, DrawableActor)

public:
	EnemyB(const char* image, SpawnPosition spawnPosition, float speed);

	virtual void Update(float deltaTime) override;

private:
	// x ��ǥ �� y ��ǥ
	float xPosition = 0.0f;
	float yPosition = 0.0f;

	// �̵� �ӵ�
	float speed = 0.0f;

	// �̵� ����
	MoveDirection moveDirection;

	// ���� ��ġ
	SpawnPosition spawnPosition;
};
