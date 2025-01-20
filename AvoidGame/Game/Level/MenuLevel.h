#pragma once

#include <Level/Level.h>
#include <vector>

struct MenuItem
{
	using OnSelected = void (*)();

	MenuItem(const char* text, OnSelected onSelected)
		: onSelected(onSelected)
	{
		size_t length = strlen(text) + 1;
		this->text = new char[length];
		strcpy_s(this->text, length, text);
	}

	~MenuItem()
	{
		delete[] text;
		text = nullptr;
	}

	char* text;

	OnSelected onSelected;
};


class MenuLevel : public Level
{
	RTTI_DECLARATIONS(MenuLevel, Level)

public:
	MenuLevel();
	~MenuLevel();

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
	std::vector<MenuItem*> items;

	// �޴� ������ ����
	int itemCount = 0;
};
