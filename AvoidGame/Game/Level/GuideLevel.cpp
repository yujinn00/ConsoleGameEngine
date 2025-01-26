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
    Engine::Get().Draw(Vector2(screenSize.x / 2 - 10, 7), "==== Guide Line ====", Color::Cyan);


    // �������� ���� �׸���
    Engine::Get().Draw(Vector2(6, 10), "Stage 01: EnemyA: 00~20��, �ʴ� 1��, óġ�� 10��", Color::Red);
    Engine::Get().Draw(Vector2(6, 11), "Stage 02: EnemyB: 20~40��, �ʴ� 2��, óġ�� 20��", Color::Yellow);
    Engine::Get().Draw(Vector2(6, 12), "Stage 03: EnemyC: 40~60��, �ʴ� 3��, óġ�� 30��", Color::Magenta);

    // ������ ���� �׸���
    Engine::Get().Draw(Vector2(14, 15), "U: Upgrade: ź�� �߻� �ӵ� ����", Color::Blue);
    Engine::Get().Draw(Vector2(14, 16), "S: Shield: ��ȸ�� ��ȣ�� ȹ��", Color::Blue);
    Engine::Get().Draw(Vector2(14, 17), "@: Bomb: ���� ������ �� ��� ����", Color::Blue);

    // �ϴܿ� �޽��� ���
    Engine::Get().Draw(Vector2(screenSize.x / 2 - 13, screenSize.y - 3), "Press Enter to continue ...", Color::Green);
}
