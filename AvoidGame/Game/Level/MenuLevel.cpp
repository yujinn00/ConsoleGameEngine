#include "MenuLevel.h"
#include "Game/Game.h"
#include "GameLevel.h"

#include <string>

MenuLevel::MenuLevel()
{
    items.emplace_back(new MenuItem(
        "< Resume Game >",
        []() {Game::Get().ToggleLevel("Resume Game"); })
    );
    items.emplace_back(new MenuItem(
        "< Go to Lobby >",
        []() {Game::Get().ToggleLevel("Return to Lobby"); })
    );

    itemCount = (int)items.size();
}

MenuLevel::~MenuLevel()
{
    for (MenuItem* item : items)
    {
        delete item;
    }

    items.clear();
}

void MenuLevel::Update(float deltaTime)
{
    Super::Update(deltaTime);

    if (Engine::Get().GetKeyDown(VK_ESCAPE))
    {
        Game::Get().ToggleLevel("Resume Game");
    }

    if (Game::Get().GetKeyDown(VK_UP))
    {
        currentSelectedIndex
            = (currentSelectedIndex - 1 + itemCount) % itemCount;
    }

    if (Game::Get().GetKeyDown(VK_DOWN))
    {
        currentSelectedIndex
            = (currentSelectedIndex + 1 + itemCount) % itemCount;
    }

    if (Game::Get().GetKeyDown(VK_RETURN))
    {
        items[currentSelectedIndex]->onSelected();
    }
}

void MenuLevel::Draw()
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

    // 이전 레벨 데이터를 참조
    GameLevel* gameLevel = Game::Get().GetPreviousLevel()->As<GameLevel>();

    if (gameLevel)
    {
        // 남은 시간 출력
        char buffer1[50];
        snprintf(buffer1, sizeof(buffer1), "Time: %d", gameLevel->GetRemainingTime());
        Engine::Get().Draw(Vector2(1, 0), buffer1, Color::Green);

        // 점수 출력
        std::string scoreText = "Score: " + std::to_string(gameLevel->GetScore());
        Engine::Get().Draw(Vector2(screenSize.x / 2 - 4, 0), scoreText.c_str(), Color::Green);

        // 탄약 발사 쿨타임 출력
        char buffer2[50];
        snprintf(buffer2, sizeof(buffer2), "Cooldown: %.1f", gameLevel->GetCooldown());
        Engine::Get().Draw(Vector2(screenSize.x - 14, 0), buffer2, Color::Green);
    }

    // 타이틀 그리기
    Engine::Get().Draw(Vector2(screenSize.x / 2 - 10, screenSize.y / 2 - 4), "====== Paused ======", Color::Yellow);

    // 메뉴 그리기
    for (int i = 0; i < itemCount; ++i)
    {
        Engine::Get().Draw(Vector2(screenSize.x / 2 - 7, screenSize.y / 2 + i - 1),
            items[i]->text,
            i == currentSelectedIndex ? selectedColor : unselectedColor);
    }
}
