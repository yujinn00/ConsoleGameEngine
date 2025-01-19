#pragma once

#include "Core.h"

// 입력 처리를 위한 구조체
struct ENGINE_API KeyState
{
	// 현재 프레임에서 키가 눌려 있는지 나타내는 변수
	bool isKeyDown = false;

	// 이전 프레임에서 키가 눌려 있었는지 나타내는 변수
	bool wasKeyDown = false;
};

// 엔진 클래스
class Level;
class Engine
{
public:
	Engine();
	virtual ~Engine();

	// 게임 루프를 실행하는 함수
	void Run();

	// 레벨을 추가하는 함수.
	void LoadLevel(Level* newLevel);

	// 입력과 관련된 함수
	bool GetKey(int key);			// 지정한 키가 눌려 있는 상태인지 반환하는 함수
	bool GetKeyDown(int key);		// 지정한 키가 현재 눌려 있고, 이전에는 눌리지 않았는지 확인하는 변수
	bool GetKeyUp(int key);			// 지정한 키가 현재 눌려 있지 않고, 이전에 눌려 있었는지 확인하는 변수

	// 게임 종료를 설정하는 함수
	void QuitGame();

	// 싱글톤 객체 접근 함수 (Engine의 전역 인스턴스를 반환하는 함수)
	static Engine& Get();

protected:
	void ProcessInput();			// 사용자 입력을 처리하는 함수
	void Update(float deltaTime);	// 게임 로직을 업데이트하는 함수
	void Draw();					// 그래픽을 렌더링하는 함수

	void SavePreviousKeyStates();	// 이전 프레임의 키 상태를 저장하는 함수

protected:
	// 게임 종료 플래그로 사용되는 변수
	bool quit;

	// 모든 키 상태를 저장하는 배열
	KeyState keyState[255];
	
	// 싱글톤 구현을 위한 전역 인스턴스
	static Engine* instance;

	// 현재 로드된 메인 레벨
	Level* mainLevel;
};
