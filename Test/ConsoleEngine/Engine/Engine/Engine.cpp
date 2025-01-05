#include "Engine.h"

#include <Windows.h>
#include <iostream>

Engine::Engine()
	: quit(false)
{
}

Engine::~Engine()
{
}

void Engine::Run()
{
	// CPU �ð� ������ ���� ����
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency); // ���ػ� Ÿ�̸��� ���ļ� �� ��������

	// ���� �ð� �ʱ�ȭ
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time); // ���� ī��Ʈ �� ��������
	int64_t currentTime = time.QuadPart;
	int64_t previousTime = 0;

	// ��ǥ ������ �ӵ� ����
	float targetFrameRate = 60.0f;
	float targetOneFrameTime = 1.0f / targetFrameRate;

	// ���� ����
	while (true)
	{
		// ���� ���� Ȯ��
		if (quit)
		{
			break;
		}

		// ���� �ð� ����
		QueryPerformanceCounter(&time);
		currentTime = time.QuadPart;

		// �ð� ���� ���
		float deltaTime = static_cast<float>(currentTime - previousTime) / static_cast<float>(frequency.QuadPart);

		// ������ ���� ���� Ȯ��
		if (deltaTime >= targetOneFrameTime)
		{
			// ������ ���� �۾�
			ProcessInput();				// ����� �Է� ó��
			Update(deltaTime);			// ���� ���� ������Ʈ
			Draw();						// ȭ�鿡 �׷��� �׸���
			SavePreviousKeyStates();	// Ű �Է� ���� ����
			
			// ���� �ð� ����
			previousTime = currentTime;
		}
	}
}

bool Engine::GetKey(int key)
{
	return keyState[key].isKeyDown;
}

bool Engine::GetKeyDown(int key)
{
	return keyState[key].isKeyDown && !keyState[key].wasKeyDown;
}

bool Engine::GetKeyUp(int key)
{
	return !keyState[key].isKeyDown && keyState[key].wasKeyDown;
}

void Engine::QuitGame()
{
	quit = true;
}

void Engine::ProcessInput()
{
	for (int i = 0; i < 255; ++i)
	{
		// GetAsyncKeyState(): �񵿱� �Լ�
		// 0x0000: �ƹ��͵� �� ����
		// 0x8000: Ű�� ���� ���� �ִ� ���¸� Ȯ���ϴ� �� ���
		// 0x0001: Ű�� ���ȴٰ� ������ �������� Ȯ���ϴ� �� ���
		// 0x8001: asdf
		keyState[i].isKeyDown = (GetAsyncKeyState(i) & 0x8000) ? true : false;
	}
}

void Engine::Update(float deltaTime)
{
	// ESC: ����
	if (GetKeyDown(VK_ESCAPE))
	{
		QuitGame();
	}

	std::cout << "DeltaTime: " << deltaTime << ", FPS: " << (1.0f / deltaTime) << "\n";
}

void Engine::Draw()
{
}

void Engine::SavePreviousKeyStates()
{
	for (int i = 0; i < 255; ++i)
	{
		keyState[i].wasKeyDown = keyState[i].isKeyDown;
	}
}
