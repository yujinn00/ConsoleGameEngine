#pragma once

// ���� ����
class Actor;
class ENGINE_API Level
{
public:
	Level();
	virtual ~Level();

	// ���� �߰� �Լ�
	void AddActor(Actor* newActor);			// ������ ���͸� �߰��ϴ� �Լ�

	// ���� ó�� �Լ�
	virtual void Update(float deltaTime);	// ������ ���͸� ������Ʈ�ϴ� �Լ�
	virtual void Draw();					// ������ ���͸� �������ϴ� �Լ�

private:
	// ���� ������ ��ġ�Ǵ� ���� �迭 (Actor*�� �迭)
	// ���α׷� ���� �߿� �迭�� ũ�⸦ �������� �����Ϸ��� ���� �����Ͱ� �ʿ���
	Actor** actors;

	// �迭�� �ִ� ũ�� (���� ������ ������ ��)
	int capacity;

	// ���� �迭�� ����� ������ ��
	int count;
};
