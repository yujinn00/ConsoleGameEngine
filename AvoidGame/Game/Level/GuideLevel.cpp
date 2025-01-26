#include "GuideLevel.h"
#include "Game/Game.h"

GuideLevel::GuideLevel()
{
}

GuideLevel::~GuideLevel()
{
}

void GuideLevel::Update(float deltaTime)
{
    Super::Update(deltaTime);

    // Enter 키를 눌렀을 때 LobbyLevel로 이동
    if (Game::Get().GetKeyDown(VK_RETURN))
    {
        Game::Get().ToggleLevel("Return to Lobby");
    }
}

void GuideLevel::Draw()
{
    Super::Draw();

    // 테두리 그리기
    Vector2 screenSize = Engine::Get().ScreenSize();
    for (int x = 0; x < screenSize.x; ++x)
    {
        Engine::Get().Draw(Vector2(x, 0), "-", Color::White);
        Engine::Get().Draw(Vector2(x, screenSize.y - 1), "-", Color::White);
    }
    for (int y = 0; y < screenSize.y; ++y)
    {
        Engine::Get().Draw(Vector2(0, y), "|", Color::White);
        Engine::Get().Draw(Vector2(screenSize.x - 1, y), "|", Color::White);
    }

    // 타이틀 그리기
    Engine::Get().Draw(Vector2(screenSize.x / 2 - 10, 7), "==== Guide Line ====", Color::Cyan);


    // 스테이지 설명 그리기
    Engine::Get().Draw(Vector2(6, 10), "Stage 01: EnemyA: 00~20초, 초당 1점, 처치당 10점", Color::Red);
    Engine::Get().Draw(Vector2(6, 11), "Stage 02: EnemyB: 20~40초, 초당 2점, 처치당 20점", Color::Yellow);
    Engine::Get().Draw(Vector2(6, 12), "Stage 03: EnemyC: 40~60초, 초당 3점, 처치당 30점", Color::Magenta);

    // 아이템 설명 그리기
    Engine::Get().Draw(Vector2(14, 15), "U: Upgrade: 탄약 발사 속도 증가", Color::Blue);
    Engine::Get().Draw(Vector2(14, 16), "S: Shield: 일회성 보호막 획득", Color::Blue);
    Engine::Get().Draw(Vector2(14, 17), "@: Bomb: 현재 레벨의 적 모두 제거", Color::Blue);

    // 하단에 메시지 출력
    Engine::Get().Draw(Vector2(screenSize.x / 2 - 13, screenSize.y - 3), "Press Enter to continue ...", Color::Green);
}
