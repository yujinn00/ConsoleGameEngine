#include "MenuLevel.h"
#include "Game/Game.h"

MenuLevel::MenuLevel()
{
    items.emplace_back(new MenuItem(
        "< Resume >",
        []() {Game::Get().ToggleLevel("Resume"); })
    );
    items.emplace_back(new MenuItem(
        "< Return >",
        []() {Game::Get().ToggleLevel("Return"); })
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
        Game::Get().ToggleLevel("Game Resume");
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

    // Draw border
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

    // Title
    Engine::Get().Draw(Vector2(screenSize.x / 2 - 9, 2), "===== PAUSED =====", Color::Yellow);

    // Menu items
    for (int i = 0; i < itemCount; ++i)
    {
        Engine::Get().Draw(Vector2(screenSize.x / 2 - 8, i + 5),
            items[i]->text,
            i == currentSelectedIndex ? selectedColor : unselectedColor);
    }
}
