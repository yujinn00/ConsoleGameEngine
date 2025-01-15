#pragma once

#include <Level/Level.h>
#include <Math/Vector2.h>

// ���ڹ� ���� ����
class DrawableActor;
class Player;
class Box;
class Target;
class GameLevel : public Level
{
	RTTI_DECLARATIONS(GameLevel, Level)

public:
	GameLevel();

	// ������ �׸��� �Լ�
	virtual void Draw() override;

	// �÷��̾ �̵��� �������� Ȯ���ϴ� �Լ�
	bool canPlayerMove(const Vector2& position);

private:
	// ��/�� ���� �迭
	List<DrawableActor*> map;

	// �ڽ� ����
	List<Box*> boxes;

	// Ÿ�� ����
	List<Target*> targets;

	// �÷��̾� ����
	Player* player = nullptr;
};
