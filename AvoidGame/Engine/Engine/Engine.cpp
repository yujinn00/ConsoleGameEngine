#include "PreCompiledHeader.h"

#include "Engine.h"
#include <Windows.h>
#include <iostream>

#include "Level/Level.h"
#include "Actor/Actor.h"

#include <time.h>

#include "Render/ScreenBuffer.h"

// �ܼ� â �޽��� �ݹ� �Լ�.
BOOL WINAPI MessageProcessor(DWORD message)
{
	switch (message)
	{
	case CTRL_CLOSE_EVENT:
		Engine::Get().QuitGame();
		return true;

	default:
		return false;
	}
}

// ����ƽ ���� �ʱ�ȭ
Engine* Engine::instance = nullptr;

Engine::Engine()
	: quit(false), mainLevel(nullptr), screenSize(80, 20)
{
	// ���� �õ� ����
	srand((unsigned int)time(nullptr));

	// �̱��� ��ü ����
	instance = this;

	// �⺻ Ÿ�� ������ �ӵ� ����
	SetTargetFrameRate(60.0f);

	// ȭ�� ���� �ʱ�ȭ
	// ���� ũ�� �Ҵ�
	imageBuffer = new CHAR_INFO[(screenSize.x + 1) * screenSize.y + 1];

	// ���� �ʱ�ȭ.
	ClearImageBuffer();

	// �� ���� ���� ���� (���۸� ������ ����ϱ� ����-���� ���۸�)
	COORD size = { (short)screenSize.x, (short)screenSize.y };
	renderTargets[0] = new ScreenBuffer(GetStdHandle(STD_OUTPUT_HANDLE), size);
	renderTargets[1] = new ScreenBuffer(size);

	// ���� ����
	Present();

	// �ܼ� â �̺�Ʈ �ݹ� �Լ� ���
	SetConsoleCtrlHandler(MessageProcessor, true);
}

Engine::~Engine()
{
	// ���� ���� �޸� ����
	if (mainLevel != nullptr)
	{
		delete mainLevel;
	}

	// Ŭ���� ���� ����
	delete[] imageBuffer;

	// ȭ�� ���� ����
	delete renderTargets[0];
	delete renderTargets[1];
}

void Engine::Run()
{
	// CPU �ð� ���
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency); // ���ػ� Ÿ�̸� ���ļ�

	// ���� �ð� �� ���� �ð��� ���� ����
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time); // ���� Ÿ�̸� ��
	int64_t currentTime = time.QuadPart;
	int64_t previousTime = currentTime;

	// Game-Loop
	while (true)
	{
		// ���� ����
		if (quit)
		{
			break;
		}

		// ���� ������ �ð� ����
		QueryPerformanceCounter(&time);
		currentTime = time.QuadPart;

		// ������ �ð� ���
		float deltaTime = static_cast<float>(currentTime - previousTime) / static_cast<float>(frequency.QuadPart);

		// ������ Ȯ��`
		if (deltaTime >= targetOneFrameTime)
		{
			// �Է� ó�� (���� Ű�� ���� ���� Ȯ��)
			ProcessInput();

			// ������Ʈ ������ ���¿����� ������ ������Ʈ ó��
			if (shouldUpdate)
			{
				Update(deltaTime);	// ������ ������Ʈ
				Draw();				// ���� ������Ʈ �׸���
			}

			// Ű ���� ����
			SavePreviousKeyStates();

			// ���� ������ �ð� ����
			previousTime = currentTime;

			// ���� ���� (���� ��û�� ���͵� ����)
			if (mainLevel)
			{
				mainLevel->ProcessAddedAndDestroyedActor();
			}

			// ������ Ȱ��ȭ
			shouldUpdate = true;
		}
	}
}

void Engine::LoadLevel(Level* newLevel)
{
	// ���� ������ �ִٸ� ���� �� ��ü

	// ���� ���� ����
	mainLevel = newLevel;
}

Level* Engine::GetCurrentLevel() const
{
	return mainLevel;
}

void Engine::AddActor(Actor* newActor)
{
	// ���� ó��
	if (mainLevel == nullptr)
	{
		return;
	}

	// ������ ���� �߰�
	shouldUpdate = false;
	mainLevel->AddActor(newActor);
}

void Engine::DestroyActor(Actor* targetActor)
{
	// ���� ó��
	if (mainLevel == nullptr)
	{
		return;
	}

	// ������ ���� ����
	shouldUpdate = false;
	targetActor->Destroy();
}

void Engine::SetCursorType(CursorType cursorType)
{
	GetRenderer()->SetCursorType(cursorType);
}

void Engine::Draw(const Vector2& position, const char* image, Color color)
{
	for (int ix = 0; ix < (int)strlen(image); ++ix)
	{
		int index = (position.y * (screenSize.x)) + position.x + ix;
		imageBuffer[index].Char.AsciiChar = image[ix];
		imageBuffer[index].Attributes = (unsigned long)color;
	}
}

void Engine::SetTargetFrameRate(float targetFrameRate)
{
	this->targetFrameRate = targetFrameRate;
	targetOneFrameTime = 1.0f / targetFrameRate;
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
	Engine::Get().
	quit = true;
}

Engine& Engine::Get()
{
	// �̱��� ��ü ��ȯ
	return *instance;
}

void Engine::ProcessInput()
{
	for (int i = 0; i < 255; ++i)
	{
		keyState[i].isKeyDown = (GetAsyncKeyState(i) & 0x8000) ? true : false;
	}
}

void Engine::Update(float deltaTime)
{
	// ���� ������Ʈ
	if (mainLevel != nullptr)
	{
		mainLevel->Update(deltaTime);
	}
}

void Engine::Clear()
{
	ClearImageBuffer();
	GetRenderer()->Clear();
}

void Engine::Draw()
{
	// ȭ�� �����
	Clear();;

	// ���� �׸���
	if (mainLevel != nullptr)
	{
		mainLevel->Draw();
	}

	// �� ���ۿ� ������ ����
	GetRenderer()->Draw(imageBuffer);

	// ����Ʈ <-> �� ���� ��ȯ
	Present();
}

void Engine::Present()
{
	// ���� ����
	SetConsoleActiveScreenBuffer(GetRenderer()->buffer);
	currentRenderTargetIndex = 1 - currentRenderTargetIndex;
}

void Engine::SavePreviousKeyStates()
{
	for (int i = 0; i < 255; ++i)
	{
		keyState[i].wasKeyDown = keyState[i].isKeyDown;
	}
}

void Engine::ClearImageBuffer()
{
	// ���� �����
	for (int y = 0; y < screenSize.y; ++y)
	{
		// ���� �����
		for (int x = 0; x < screenSize.x + 1; ++x)
		{
			auto& buffer = imageBuffer[(y * (screenSize.x + 1)) + x];
			buffer.Char.AsciiChar = ' ';
			buffer.Attributes = 0;
		}

		// �� �� ���� ���� ���� �߰�
		auto& buffer = imageBuffer[(y * (screenSize.x + 1)) + screenSize.x];
		buffer.Char.AsciiChar = '\n';
		buffer.Attributes = 0;
	}

	// �������� �� ���� �߰�
	auto& buffer = imageBuffer[(screenSize.x + 1) * screenSize.y];
	buffer.Char.AsciiChar = '\0';
	buffer.Attributes = 0;
}
