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

    // ���� ���� �����͸� ����
    GameLevel* gameLevel = Game::Get().GetPreviousLevel()->As<GameLevel>();

    if (gameLevel)
    {
        // ���� �ð� ���
        char buffer1[50];
        snprintf(buffer1, sizeof(buffer1), "Time: %d", gameLevel->GetRemainingTime());
        Engine::Get().Draw(Vector2(1, 0), buffer1, Color::Green);

        // ���� ���
        std::string scoreText = "Score: " + std::to_string(gameLevel->GetScore());
        Engine::Get().Draw(Vector2(screenSize.x / 2 - 4, 0), scoreText.c_str(), Color::Green);

        // ź�� �߻� ��Ÿ�� ���
        char buffer2[50];
        snprintf(buffer2, sizeof(buffer2), "Cooldown: %.1f", gameLevel->GetCooldown());
        Engine::Get().Draw(Vector2(screenSize.x - 14, 0), buffer2, Color::Green);
    }

    // Ÿ��Ʋ �׸���
    Engine::Get().Draw(Vector2(screenSize.x / 2 - 10, screenSize.y / 2 - 4), "====== Paused ======", Color::Yellow);

    // �޴� �׸���
    for (int i = 0; i < itemCount; ++i)
    {
        Engine::Get().Draw(Vector2(screenSize.x / 2 - 7, screenSize.y / 2 + i - 1),
            items[i]->text,
            i == currentSelectedIndex ? selectedColor : unselectedColor);
    }
}
