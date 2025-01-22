#include "RankLevel.h"
#include "Game/Game.h"

#include <fstream>
#include <vector>
#include <string>

RankLevel::RankLevel()
{
}

RankLevel::~RankLevel()
{
}

void RankLevel::Update(float deltaTime)
{
    Super::Update(deltaTime);

    // Enter Ű�� ������ �� LobbyLevel�� �̵�
    if (Game::Get().GetKeyDown(VK_RETURN))
    {
        Game::Get().ToggleLevel("Return to Lobby");
    }
}

void RankLevel::Draw()
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
    // @Todo: ��ǥ ����
    Engine::Get().Draw(Vector2(screenSize.x / 2 - 7, 2), "=== LeaderBoard ===", Color::Cyan);

    LoadScore();

    // �ϴܿ� �޽��� ���
    // @Todo: ��ǥ ����
    Engine::Get().Draw(Vector2(screenSize.x / 2 - 15, screenSize.y - 3), "Press Enter to continue ...", Color::Green);
}

void RankLevel::LoadScore()
{
    // ȭ�� ũ�� �ҷ�����
    Vector2 screenSize = Engine::Get().ScreenSize();

    // ��ŷ ������ �б�
    std::ifstream fin("Rank.txt");
    if (!fin.is_open() || fin.peek() == std::ifstream::traits_type::eof())
    {
        // @Todo: ��ǥ ����
        Engine::Get().Draw(Vector2(screenSize.x / 2 - 10, 5), "Data not found ...", Color::White);
    }
    else
    {
        std::vector<std::string> ranks;
        std::string line;
        while (std::getline(fin, line))
        {
            ranks.push_back(line);
        }
        fin.close();

        // �� ���� ����
        const int lineHeight = 2;
        int yOffset = 5;

        // @Todo: ������ �ؾ� ��
        // ���� 10������� ���
        for (int i = 0; i < ranks.size() && i < 10; ++i)
        {
            if (i == 0)
            {
                std::string st = "1st - " + ranks[i];
                Engine::Get().Draw(Vector2(screenSize.x / 2 - 10, yOffset), st.c_str(), Color::White);
            }
            else if (i == 1)
            {
                std::string nd = "2nd - " + ranks[i];
                Engine::Get().Draw(Vector2(screenSize.x / 2 - 10, yOffset), nd.c_str(), Color::White);
            }
            else if (i == 2)
            {
                std::string rd = "3rd - " + ranks[i];
                Engine::Get().Draw(Vector2(screenSize.x / 2 - 10, yOffset), rd.c_str(), Color::White);
            }
            else
            {
                std::string th = std::to_string(i + 1) + "th - " + ranks[i];
                Engine::Get().Draw(Vector2(screenSize.x / 2 - 10, yOffset), th.c_str(), Color::White);
            }
            yOffset += lineHeight;
        }
    }
}
