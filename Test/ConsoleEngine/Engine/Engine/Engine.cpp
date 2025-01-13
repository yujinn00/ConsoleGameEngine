#include "PreCompiledHeader.h"

#include "Engine.h"
#include <Windows.h>
#include <iostream>
#include "Level/Level.h"

// �̱��� ����ƽ ���� �ʱ�ȭ
Engine* Engine::instance = nullptr;

Engine::Engine()
	: quit(false), mainLevel(nullptr)
{
	// �̱��� ��ü ����
	instance = this;
}

Engine::~Engine()
{
	// ���� ���� ����
	if (mainLevel != nullptr)
	{
		delete mainLevel;
	}
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

void Engine::LoadLevel(Level* newLevel)
{
	if (mainLevel != nullptr)
	{
		delete mainLevel; // ���� ���� ����
	}

	mainLevel = newLevel; // �� ���� ����
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

Engine& Engine::Get()
{
	return *instance;
}

void Engine::ProcessInput()
{
	for (int i = 0; i < 255; ++i)
	{
		// GetAsyncKeyState(): �񵿱� �Լ�
		// 0x0000: �ƹ� Ű�� ������ ���� ����
		// 0x8000: Ű�� ���� ���� �ִ� ���¸� Ȯ���ϴ� �� ���
		// 0x0001: Ű�� ���ȴٰ� ������ �������� Ȯ���ϴ� �� ���
		// 0x8001: Ű�� ���� �ִ� ���¿��� ���ȴٰ� ������ ���¸� ���ÿ� Ȯ��
		keyState[i].isKeyDown = (GetAsyncKeyState(i) & 0x8000) ? true : false;
	}
}

void Engine::Update(float deltaTime)
{
	if (mainLevel != nullptr)
	{
		mainLevel->Update(deltaTime); // ���� ������Ʈ
	}
}

void Engine::Draw()
{
	if (mainLevel != nullptr)
	{
		mainLevel->Draw(); // ���� ������
	}
}

void Engine::SavePreviousKeyStates()
{
	for (int i = 0; i < 255; ++i)
	{
		keyState[i].wasKeyDown = keyState[i].isKeyDown;
	}
}
