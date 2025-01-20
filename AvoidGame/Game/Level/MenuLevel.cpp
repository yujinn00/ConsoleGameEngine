#include "MenuLevel.h"
#include "Game/Game.h"

MenuLevel::MenuLevel()
{
	items.emplace_back(new MenuItem(
		"Game Resume",
		[]() {Game::Get().ToggleLevel("Game Resume"); })
	);
	items.emplace_back(new MenuItem(
		"Return to Lobby",
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

	Engine::Get().Draw(Vector2(0, 0), "Game Paused");

	for (int ix = 0; ix < itemCount; ++ix)
	{
		Engine::Get().Draw(Vector2(0, 2 + ix), items[ix]->text, ix == currentSelectedIndex ? selectedColor : unselectedColor);
	}
}
