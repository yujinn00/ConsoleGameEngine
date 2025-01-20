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
	// 현재 선택된 메뉴 번호 (인덱스)
	int currentSelectedIndex = 0;

	// 선택된 메뉴의 색상
	Color selectedColor = Color::Green;

	// 선택되지 않은 메뉴의 색상
	Color unselectedColor = Color::White;

	// 메뉴 저장소
	std::vector<MenuItem*> items;

	// 메뉴 아이템 개수
	int itemCount = 0;
};
