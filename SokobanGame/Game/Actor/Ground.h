#pragma once

#include <Actor/DrawableActor.h>

// �÷��̾ �ɾ�ٴ� �� �ִ� �ٴ� ����
class Ground : public DrawableActor
{
	RTTI_DECLARATIONS(Ground, DrawableActor)

public:
	Ground(const Vector2& position);
};
