#include "LobbyLevel.h"
#include "Game/Game.h"

LobbyLevel::LobbyLevel()
{
	items.emplace_back(new LobbyItem(
		"Game Start",
		[]() {Game::Get().ToggleLevel("Game Start"); })
	);
	items.emplace_back(new LobbyItem(
		"Game Quit",
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

	Engine::Get().Draw(Vector2(0, 0), "Avoid Game");

	for (int ix = 0; ix < itemCount; ++ix)
	{
		Engine::Get().Draw(Vector2(0, 3 + ix), items[ix]->text, ix == currentSelectedIndex ? selectedColor : unselectedColor);
	}
}
