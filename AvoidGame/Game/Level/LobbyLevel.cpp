#include "LobbyLevel.h"
#include "Game/Game.h"

LobbyLevel::LobbyLevel()
{
    items.emplace_back(new LobbyItem(
        "< Start >",
        []() {Game::Get().ToggleLevel("Play Game"); })
    );
    items.emplace_back(new LobbyItem(
        "< Quit Game >",
        []() {Game::Get().QuitGame(); })
    );

    itemCount = (int)items.size();
}

LobbyLevel::~LobbyLevel()
{
    for (LobbyItem* item : items)
    {
        delete item;
    }

    items.clear();
}

void LobbyLevel::Update(float deltaTime)
{
    Super::Update(deltaTime);

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

void LobbyLevel::Draw()
{
    Super::Draw();

    // 테두리
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

    // 제목
    Engine::Get().Draw(Vector2(screenSize.x / 2 - 9, 2), "===== LOBBY =====", Color::Cyan);

    // 메뉴
    for (int i = 0; i < itemCount; ++i)
    {
        Engine::Get().Draw(Vector2(screenSize.x / 2 - 7, i + 5),
            items[i]->text,
            i == currentSelectedIndex ? selectedColor : unselectedColor);
    }
}
