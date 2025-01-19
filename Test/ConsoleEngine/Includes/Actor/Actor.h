#pragma once

#include "Core.h"
#include "RTTI.h"

// ������ �⺻ ��ü
class ENGINE_API Actor : public RTTI
{
	// RTTI ����
	RTTI_DECLARATIONS(Actor, RTTI)

public:
	Actor();
	virtual ~Actor();

	// ���� ó�� �Լ�
	virtual void Update(float deltaTime);
	virtual void Draw();

protected:
	// Ȱ��ȭ �������� ��Ÿ���� ����
	bool isActive;

	// ������ ���� ��û�� �ƴ��� ��Ÿ���� ����
	bool isExpired;
};
