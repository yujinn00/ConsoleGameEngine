#include "target.h"

Target::Target(const Vector2& position)
	: DrawableActor("T")
{
	// ��ġ ����
	this->position = position;

	// ���� ����
	color = Color::Blue;
}
