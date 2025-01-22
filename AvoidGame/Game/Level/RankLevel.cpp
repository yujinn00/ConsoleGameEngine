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

    // Enter 키를 눌렀을 때 LobbyLevel로 이동
    if (Game::Get().GetKeyDown(VK_RETURN))
    {
        Game::Get().ToggleLevel("Return to Lobby");
    }
}

void RankLevel::Draw()
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
    // @Todo: 좌표 수정
    Engine::Get().Draw(Vector2(screenSize.x / 2 - 7, 2), "=== LeaderBoard ===", Color::Cyan);

    LoadScore();

    // 하단에 메시지 출력
    // @Todo: 좌표 수정
    Engine::Get().Draw(Vector2(screenSize.x / 2 - 15, screenSize.y - 3), "Press Enter to continue ...", Color::Green);
}

void RankLevel::LoadScore()
{
    // 화면 크기 불러오기
    Vector2 screenSize = Engine::Get().ScreenSize();

    // 랭킹 데이터 읽기
    std::ifstream fin("Rank.txt");
    if (!fin.is_open() || fin.peek() == std::ifstream::traits_type::eof())
    {
        // @Todo: 좌표 수정
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

        // 줄 간격 설정
        const int lineHeight = 2;
        int yOffset = 5;

        // @Todo: 포매팅 해야 함
        // 상위 10등까지만 출력
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
