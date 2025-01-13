#include "PreCompiledHeader.h"

#include "Engine.h"
#include <Windows.h>
#include <iostream>
#include "Level/Level.h"

// 싱글톤 스태틱 변수 초기화
Engine* Engine::instance = nullptr;

Engine::Engine()
	: quit(false), mainLevel(nullptr)
{
	// 싱글톤 객체 설정
	instance = this;
}

Engine::~Engine()
{
	// 메인 레벨 삭제
	if (mainLevel != nullptr)
	{
		delete mainLevel;
	}
}

void Engine::Run()
{
	// CPU 시간 측정을 위한 설정
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency); // 고해상도 타이머의 주파수 값 가져오기

	// 현재 시간 초기화
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time); // 현재 카운트 값 가져오기
	int64_t currentTime = time.QuadPart;
	int64_t previousTime = 0;

	// 목표 프레임 속도 설정
	float targetFrameRate = 60.0f;
	float targetOneFrameTime = 1.0f / targetFrameRate;

	// 게임 루프
	while (true)
	{
		// 종료 조건 확인
		if (quit)
		{
			break;
		}

		// 현재 시간 측정
		QueryPerformanceCounter(&time);
		currentTime = time.QuadPart;

		// 시간 간격 계산
		float deltaTime = static_cast<float>(currentTime - previousTime) / static_cast<float>(frequency.QuadPart);

		// 프레임 실행 여부 확인
		if (deltaTime >= targetOneFrameTime)
		{
			// 프레임 실행 작업
			ProcessInput();				// 사용자 입력 처리
			Update(deltaTime);			// 게임 로직 업데이트
			Draw();						// 화면에 그래픽 그리기
			SavePreviousKeyStates();	// 키 입력 상태 저장
			
			// 이전 시간 갱신
			previousTime = currentTime;
		}
	}
}

void Engine::LoadLevel(Level* newLevel)
{
	if (mainLevel != nullptr)
	{
		delete mainLevel; // 기존 레벨 삭제
	}

	mainLevel = newLevel; // 새 레벨 설정
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
		// GetAsyncKeyState(): 비동기 함수
		// 0x0000: 아무 키도 눌리지 않은 상태
		// 0x8000: 키가 현재 눌려 있는 상태를 확인하는 데 사용
		// 0x0001: 키가 눌렸다가 떼어진 상태인지 확인하는 데 사용
		// 0x8001: 키가 눌려 있는 상태에서 눌렸다가 떼어진 상태를 동시에 확인
		keyState[i].isKeyDown = (GetAsyncKeyState(i) & 0x8000) ? true : false;
	}
}

void Engine::Update(float deltaTime)
{
	if (mainLevel != nullptr)
	{
		mainLevel->Update(deltaTime); // 레벨 업데이트
	}
}

void Engine::Draw()
{
	if (mainLevel != nullptr)
	{
		mainLevel->Draw(); // 레벨 렌더링
	}
}

void Engine::SavePreviousKeyStates()
{
	for (int i = 0; i < 255; ++i)
	{
		keyState[i].wasKeyDown = keyState[i].isKeyDown;
	}
}
