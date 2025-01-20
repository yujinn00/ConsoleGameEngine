#pragma once

#include <Level/Level.h>
#include <vector>

struct LobbyItem
{
	using OnSelected = void (*)();

	LobbyItem(const char* text, OnSelected onSelected)
		: onSelected(onSelected)
	{
		size_t length = strlen(text) + 1;
		this->text = new char[length];
		strcpy_s(this->text, length, text);
	}

	~LobbyItem()
	{
		delete[] text;
		text = nullptr;
	}

	char* text;

	OnSelected onSelected;
};

class LobbyLevel : public Level
{
	RTTI_DECLARATIONS(LobbyLevel, Level)

public:
	LobbyLevel();
	~LobbyLevel();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

private:
	// ���� ���õ� �޴� ��ȣ (�ε���)
	int currentSelectedIndex = 0;

	// ���õ� �޴��� ����
	Color selectedColor = Color::Green;

	// ���õ��� ���� �޴��� ����
	Color unselectedColor = Color::White;

	// �޴� �����
	std::vector<LobbyItem*> items;

	// �޴� ������ ����
	int itemCount = 0;
};
