#include "Wall.h"

Wall::Wall(const Vector2& position)
	: DrawableActor("1")
{
	// ��ġ ����
	this->position = position;

	// ���� ����
	color = Color::Green;
}
