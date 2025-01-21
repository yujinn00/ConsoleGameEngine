#include "Upgrade.h"
#include "Engine/Engine.h"

Upgrade::Upgrade(const char* image)
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

void Upgrade::Update(float deltaTime)
{
	Super::Update(deltaTime);
}
