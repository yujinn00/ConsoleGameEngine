#include "ClearLevel.h"
#include "Game/Game.h"

ClearLevel::ClearLevel()
{
}

ClearLevel::~ClearLevel()
{
}

void ClearLevel::Update(float deltaTime)
{
    Super::Update(deltaTime);

    // Enter Ű�� ������ �� LobbyLevel�� �̵�
    if (Game::Get().GetKeyDown(VK_RETURN))
    {
        Game::Get().ToggleLevel("Return to Lobby");
    }
}

void ClearLevel::Draw()
{
    Super::Draw();

    // �׵θ� �׸���
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

    // ���� ���� �׸���
    Engine::Get().Draw(Vector2(13, 11), " ####  #      #####    #    #### ", Color::Cyan);
    Engine::Get().Draw(Vector2(13, 12), "#      #      #       # #   #   #", Color::Cyan);
    Engine::Get().Draw(Vector2(13, 13), "#      #      #####  #####  #### ", Color::Cyan);
    Engine::Get().Draw(Vector2(13, 14), "#      #      #      #   #  #  # ", Color::Cyan);
    Engine::Get().Draw(Vector2(13, 15), " ####  #####  #####  #   #  #   #", Color::Cyan);

    // �ϴܿ� �޽��� ���
    Engine::Get().Draw(Vector2(screenSize.x / 2 - 13, screenSize.y - 3), "Press Enter to continue ...", Color::Green);
}
