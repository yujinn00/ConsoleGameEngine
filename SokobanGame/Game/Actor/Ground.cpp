#include "Ground.h"

Ground::Ground(const Vector2& position)
	: DrawableActor(".")
{
	// ��ġ ����
	this->position = position;

	// ���� ����
	color = Color::Red;
}
