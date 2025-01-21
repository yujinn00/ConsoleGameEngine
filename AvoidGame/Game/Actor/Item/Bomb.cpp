#include "Bomb.h"
#include "Engine/Engine.h"

Bomb::Bomb(const char* image)
	: DrawableActor(image)
{
	color = Color::Blue;

	// 맵 크기 가져오기
	Vector2 screenSize = Engine::Get().ScreenSize();

	// 랜덤 위치 생성
	int xPosition = Random(1, screenSize.x - width - 1);
	int yPosition = Random(1, screenSize.y - width - 1);

	// 초기 위치 설정
	SetPosition(Vector2(xPosition, yPosition));
}

void Bomb::Update(float deltaTime)
{
	Super::Update(deltaTime);
}
