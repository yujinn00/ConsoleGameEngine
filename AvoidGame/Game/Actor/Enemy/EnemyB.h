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
	float xPosition;
	float yPosition;

	// �̵� �ӵ�
	float speed;

	// �̵� ����
	MoveDirection moveDirection = MoveDirection::None;

	// ���� ��ġ
	SpawnPosition spawnPosition;
};
