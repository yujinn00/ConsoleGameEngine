#pragma once

#include "Core.h"

// �Է� ó���� ���� ����ü
struct ENGINE_API KeyState
{
	// ���� �����ӿ��� Ű�� ���� �ִ��� ��Ÿ���� ����
	bool isKeyDown = false;

	// ���� �����ӿ��� Ű�� ���� �־����� ��Ÿ���� ����
	bool wasKeyDown = false;
};

// ���� Ŭ����
class Level;
class Engine
{
public:
	Engine();
	virtual ~Engine();

	// ���� ������ �����ϴ� �Լ�
	void Run();

	// ������ �߰��ϴ� �Լ�.
	void LoadLevel(Level* newLevel);

	// �Է°� ���õ� �Լ�
	bool GetKey(int key);			// ������ Ű�� ���� �ִ� �������� ��ȯ�ϴ� �Լ�
	bool GetKeyDown(int key);		// ������ Ű�� ���� ���� �ְ�, �������� ������ �ʾҴ��� Ȯ���ϴ� ����
	bool GetKeyUp(int key);			// ������ Ű�� ���� ���� ���� �ʰ�, ������ ���� �־����� Ȯ���ϴ� ����

	// ���� ���Ḧ �����ϴ� �Լ�
	void QuitGame();

	// �̱��� ��ü ���� �Լ� (Engine�� ���� �ν��Ͻ��� ��ȯ�ϴ� �Լ�)
	static Engine& Get();

protected:
	void ProcessInput();			// ����� �Է��� ó���ϴ� �Լ�
	void Update(float deltaTime);	// ���� ������ ������Ʈ�ϴ� �Լ�
	void Draw();					// �׷����� �������ϴ� �Լ�

	void SavePreviousKeyStates();	// ���� �������� Ű ���¸� �����ϴ� �Լ�

protected:
	// ���� ���� �÷��׷� ���Ǵ� ����
	bool quit;

	// ��� Ű ���¸� �����ϴ� �迭
	KeyState keyState[255];
	
	// �̱��� ������ ���� ���� �ν��Ͻ�
	static Engine* instance;

	// ���� �ε�� ���� ����
	Level* mainLevel;
};
