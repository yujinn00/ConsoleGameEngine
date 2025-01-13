#pragma once

// ������ �⺻ ��ü
class ENGINE_API Actor
{
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
