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
	// 현재 선택된 메뉴 번호 (인덱스)
	int currentSelectedIndex = 0;

	// 선택된 메뉴의 색상
	Color selectedColor = Color::Green;

	// 선택되지 않은 메뉴의 색상
	Color unselectedColor = Color::White;

	// 메뉴 저장소
	std::vector<LobbyItem*> items;

	// 메뉴 아이템 개수
	int itemCount = 0;
};
