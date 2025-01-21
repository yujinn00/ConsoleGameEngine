#include "Bomb.h"
#include "Engine/Engine.h"

Bomb::Bomb(const char* image)
	: DrawableActor(image)
{
	color = Color::Blue;

	// �� ũ�� ��������
	Vector2 screenSize = Engine::Get().ScreenSize();

	// ���� ��ġ ����
	int xPosition = Random(1, screenSize.x - width - 1);
	int yPosition = Random(1, screenSize.y - width - 1);

	// �ʱ� ��ġ ����
	SetPosition(Vector2(xPosition, yPosition));
}

void Bomb::Update(float deltaTime)
{
	Super::Update(deltaTime);
}
