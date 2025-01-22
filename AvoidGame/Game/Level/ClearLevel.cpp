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
    // @Todo: ��ǥ ����
    //Engine::Get().Draw(Vector2(2, 2), " ####    #    #   #  #####     ###   #   #  #####  #### ", Color::Cyan);
    //Engine::Get().Draw(Vector2(2, 3), "#       # #   ## ##  #        #   #  #   #  #      #   #", Color::Cyan);
    //Engine::Get().Draw(Vector2(2, 4), "#  ##  #####  # # #  #####    #   #  #   #  #####  #### ", Color::Cyan);
    //Engine::Get().Draw(Vector2(2, 5), "#   #  #   #  #   #  #        #   #   # #   #      #  # ", Color::Cyan);
    //Engine::Get().Draw(Vector2(2, 6), " ####  #   #  #   #  #####     ###     #    #####  #   #", Color::Cyan);
    Engine::Get().Draw(Vector2(13, 2), " ####  #      #####    #    #### ", Color::Cyan);
    Engine::Get().Draw(Vector2(13, 3), "#      #      #       # #   #   #", Color::Cyan);
    Engine::Get().Draw(Vector2(13, 4), "#      #      #####  #####  #### ", Color::Cyan);
    Engine::Get().Draw(Vector2(13, 5), "#      #      #      #   #  #  # ", Color::Cyan);
    Engine::Get().Draw(Vector2(13, 6), " ####  #####  #####  #   #  #   #", Color::Cyan);

    // �ϴܿ� �޽��� ���
    // @Todo: ��ǥ ����
    Engine::Get().Draw(Vector2(screenSize.x / 2 - 15, screenSize.y - 3), "Press Enter to continue ...", Color::Green);
}
