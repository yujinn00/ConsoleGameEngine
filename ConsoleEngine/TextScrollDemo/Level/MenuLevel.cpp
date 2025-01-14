#include "MenuLevel.h"
#include "Game/Game.h"

MenuLevel::MenuLevel()
{
	// �޴� �ʱ�ȭ
	items.emplace_back(new MenuItem(
		"Resume Game",
		[]() { Game::Get().ToggleMenu(); })
	);
	items.emplace_back(new MenuItem(
		"Quit Game",
		[]() { Game::Get().QuitGame(); })
	);

	// �޴� ���� ����
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

	// ESC�� ������ �޴� ���
	if (Game::Get().GetKeyDown(VK_ESCAPE))
	{
		Game::Get().ToggleMenu();
	}

	// �� ����Ű
	if (Game::Get().GetKeyDown(VK_UP))
	{
		// �ε��� ��ȯ
		currentSelectedIndex = (currentSelectedIndex - 1 + itemCount) % itemCount;
	}

	// �Ʒ� ����Ű
	if (Game::Get().GetKeyDown(VK_DOWN))
	{
		// �ε��� ��ȯ
		currentSelectedIndex = (currentSelectedIndex + 1) % itemCount;
	}

	// ����Ű
	if (Game::Get().GetKeyDown(VK_RETURN))
	{
		items[currentSelectedIndex]->onSelected();
	}
}

void MenuLevel::Draw()
{
	Super::Draw();

	// �޴� ���� ���
	static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, unselectedColor);
	std::cout << "Tedxt Scroll Demo Menu\n\n";

	// ���� ��ȸ�ϸ鼭 �޴� �ؽ�Ʈ ���
	for (int i = 0; i < itemCount; ++i)
	{
		// ���� ����
		SetConsoleTextAttribute(handle, i == currentSelectedIndex ? selectedColor : unselectedColor);

		// ���
		std::cout << items[i]->text << "\n";
	}
}
