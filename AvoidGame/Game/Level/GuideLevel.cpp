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

    // Enter Ű�� ������ �� LobbyLevel�� �̵�
    if (Game::Get().GetKeyDown(VK_RETURN))
    {
        Game::Get().ToggleLevel("Return to Lobby");
    }
}

void GuideLevel::Draw()
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

    // Ÿ��Ʋ �׸���
    Engine::Get().Draw(Vector2(screenSize.x / 2 - 10, 2), "==== Guide Line ====", Color::Cyan);


    // ���� ���� �׸���
    Engine::Get().Draw(Vector2(13, 5), "Stage 01: EnemyA: �ʴ� 1��, óġ�� 10��", Color::White);
    Engine::Get().Draw(Vector2(13, 6), "Stage 02: EnemyB: �ʴ� 2��, óġ�� 20��", Color::White);
    Engine::Get().Draw(Vector2(13, 7), "Stage 03: EnemyC: �ʴ� 3��, óġ�� 30��", Color::White);

    Engine::Get().Draw(Vector2(13, 9), "U: Upgrade: ź�� �߻� �ӵ� ����", Color::Blue);
    Engine::Get().Draw(Vector2(13, 10), "S: Shield: ��ȸ�� ��ȣ�� ȹ��", Color::Blue);
    Engine::Get().Draw(Vector2(13, 11), "@: Bomb: ���� ������ �� ��� ����", Color::Blue);

    // �ϴܿ� �޽��� ���
    Engine::Get().Draw(Vector2(screenSize.x / 2 - 13, screenSize.y - 3), "Press Enter to continue ...", Color::Green);
}
