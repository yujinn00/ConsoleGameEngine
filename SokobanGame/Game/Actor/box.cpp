#include "box.h"

Box::Box(const Vector2& position)
	: DrawableActor("b")
{
	// ��ġ ����
	this->position = position;

	// ���� ����
	color = Color::White;
}
