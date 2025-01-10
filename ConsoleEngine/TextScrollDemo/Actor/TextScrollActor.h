#pragma once

#include <Actor/Actor.h>

class TextScrollActor : public Actor
{
	RTTI_DECLARATIONS(TextScrollActor, Actor)

public:
	TextScrollActor(const char* message);
	~TextScrollActor();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

private:
	// ȭ�鿡 ������ ���ڿ� ��
	char* string = nullptr;

	// ���ڿ� ����
	int length = 0;

	// ȭ�鿡 ������ ���ڿ��� ���� �ε���
	int index = 0;

	// ȭ�鿡 ������ ���� ����
	int printWidth = 20;

	// �����̸� ���� ����
	float elapsedTime = 0.0f;
	float delayTime = 0.1f;
};
