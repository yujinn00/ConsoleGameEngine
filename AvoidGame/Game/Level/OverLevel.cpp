#include "OverLevel.h"
#include "Game/Game.h"

OverLevel::OverLevel()
{
}

OverLevel::~OverLevel()
{
}

void OverLevel::Update(float deltaTime)
{
    Super::Update(deltaTime);

    // Enter 키를 눌렀을 때 LobbyLevel로 이동
    if (Game::Get().GetKeyDown(VK_RETURN))
    {
        Game::Get().ToggleLevel("Return to Lobby");
    }
}

void OverLevel::Draw()
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

    // 게임 오버 그리기
    // @Todo: 좌표 수정
    Engine::Get().Draw(Vector2(2, 2), " ####    #    #   #  #####     ###   #   #  #####  #### ", Color::Cyan);
    Engine::Get().Draw(Vector2(2, 3), "#       # #   ## ##  #        #   #  #   #  #      #   #", Color::Cyan);
    Engine::Get().Draw(Vector2(2, 4), "#  ##  #####  # # #  #####    #   #  #   #  #####  #### ", Color::Cyan);
    Engine::Get().Draw(Vector2(2, 5), "#   #  #   #  #   #  #        #   #   # #   #      #  # ", Color::Cyan);
    Engine::Get().Draw(Vector2(2, 6), " ####  #   #  #   #  #####     ###     #    #####  #   #", Color::Cyan);

    // 하단에 메시지 출력
    // @Todo: 좌표 수정
    Engine::Get().Draw(Vector2(screenSize.x / 2 - 15, screenSize.y - 3), "Press Enter to continue ...", Color::Green);
}
