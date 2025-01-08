#pragma once

#include "Core.h"
#include "RTTI.h"
#include "Math/Vector2.h"

// ������ �⺻ ��ü
class ENGINE_API Actor : public RTTI
{
	// RTTI ����
	// ��Ÿ�ӿ� ������ Ÿ���� Ȯ���ϱ� ���� �۾�
	// dynamic_cast �����ڸ� Ȱ���ؾ� �ϴµ�, ������ ���� Ŀ���� ���� ���
	RTTI_DECLARATIONS(Actor, RTTI)

public:
	Actor();
	virtual ~Actor();

	// ���� ó�� �Լ�
	virtual void Update(float deltaTime);
	virtual void Draw();

	// Getter / Setter
	virtual void SetPosition(const Vector2& newPosition);
	inline Vector2 GetPosition() const;

protected:
	// ������ ��ġ
	Vector2 position;

	// ID(�ؽ�) / �̸� ��

	// Ȱ��ȭ ���������� ��Ÿ���� ����
	bool isActice;

	// ������ ���� ��û�� �ƴ��� ���θ� ��Ÿ���� ����
	bool isExpired;
};
