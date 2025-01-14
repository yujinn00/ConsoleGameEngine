#pragma once

#include "Engine/Engine.h"

class Game : public Engine
{
public:
	Game();
	~Game();

	// �޴��� - ����� ��ȯ �Լ�
	void ToggleMenu();

	// �̱��� ���� �Լ�
	static Game& Get() { return *instance; }

private:
	// �޴��� �����ְ� �ִ��� ��Ÿ���� ����
	bool showMenu = false;

	// �� ����
	Level* menuLevel = nullptr;
	Level* backLevel = nullptr;

	// �̱��� ���� ��ü
	static Game* instance;
};
