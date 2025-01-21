#include "Shield.h"
#include "Engine/Engine.h"

Shield::Shield(const char* image)
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

void Shield::Update(float deltaTime)
{
	Super::Update(deltaTime);
}
