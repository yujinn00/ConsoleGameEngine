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
	// ID(�ؽ�) / �̸� ��

	// Ȱ��ȭ ���������� ��Ÿ���� ����
	bool isActice;

	// ������ ���� ��û�� �ƴ��� ���θ� ��Ÿ���� ����
	bool isExpired;
};
