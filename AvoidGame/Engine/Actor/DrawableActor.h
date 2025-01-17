#pragma once

#include "Core.h"
#include "Actor.h"

class ENGINE_API DrawableActor : public Actor
{
	// RTTI
	RTTI_DECLARATIONS(DrawableActor, Actor)

public:
	DrawableActor(const char* image = "");
	virtual ~DrawableActor();

	virtual void Draw() override;
	virtual void SetPosition(const Vector2& newPosition) override;

	// �浹 Ȯ�� �Լ�
	bool Intersect(const DrawableActor& other);

	// ����
	inline int Width() const { return width; }

protected:
	// ȭ�鿡 �׸� ���� ��
	char* image;

	// �ʺ� (���ڿ� ����)
	int width = 0;

	// ���� ��
	Color color = Color::White;
};
