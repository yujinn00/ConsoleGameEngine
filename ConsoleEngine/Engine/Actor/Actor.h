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

	// Level Ŭ������ friend�� ����
	// private�� ������ �����ϰ� �ϱ� ����
	friend class Level;

public:
	Actor();
	virtual ~Actor();

	// ���� ó�� �Լ�
	virtual void Update(float deltaTime);
	virtual void Draw();

	// Getter / Setter
	virtual void SetPosition(const Vector2& newPosition);
	inline Vector2 GetPosition() const;

	inline bool IsActive() const { return isActive; }
	inline void SetActive(bool active) { isActive = active; }
	inline void Destroy() { isExpired = true; }

protected:
	// ������ ��ġ
	Vector2 position;

	// ID(�ؽ�) / �̸� ��

	// Ȱ��ȭ ���������� ��Ÿ���� ����
	bool isActive;

	// ������ ���� ��û�� �ƴ��� ���θ� ��Ÿ���� ����
	bool isExpired;
};
