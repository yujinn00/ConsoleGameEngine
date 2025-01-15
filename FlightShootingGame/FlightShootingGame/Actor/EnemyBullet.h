#pragma once

#include <Actor/DrawableActor.h>

class EnemyBullet : public DrawableActor
{
	RTTI_DECLARATIONS(EnemyBullet, DrawableActor)

public:
	EnemyBullet(const Vector2& position);

	virtual void Update(float deltaTime) override;

private:
	// �̵� ���� ����
	float speed = 15.0f;
	float yPosition = 0.0f;
};