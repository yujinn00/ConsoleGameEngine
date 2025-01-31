#include "OverLevel.h"
#include "Game/Game.h"

#include <string>

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
    Engine::Get().Draw(Vector2(2, 11), " ####    #    #   #  #####     ###   #   #  #####  #### ", Color::Cyan);
    Engine::Get().Draw(Vector2(2, 12), "#       # #   ## ##  #        #   #  #   #  #      #   #", Color::Cyan);
    Engine::Get().Draw(Vector2(2, 13), "#  ##  #####  # # #  #####    #   #  #   #  #####  #### ", Color::Cyan);
    Engine::Get().Draw(Vector2(2, 14), "#   #  #   #  #   #  #        #   #   # #   #      #  # ", Color::Cyan);
    Engine::Get().Draw(Vector2(2, 15), " ####  #   #  #   #  #####     ###     #    #####  #   #", Color::Cyan);

    // 점수 출력
    int score = Game::Get().GetScore();
    std::string scoreText = "Your Score: " + std::to_string(score);
    Engine::Get().Draw(Vector2(screenSize.x / 2 - scoreText.length() / 2, screenSize.y / 2 - 6), scoreText.c_str(), Color::White);

    // 하단에 메시지 출력
    Engine::Get().Draw(Vector2(screenSize.x / 2 - 13, screenSize.y - 3), "Press Enter to continue ...", Color::Green);
}
