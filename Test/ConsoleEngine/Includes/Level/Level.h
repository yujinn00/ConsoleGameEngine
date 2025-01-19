#pragma once

// 전방 선언
class Actor;
class ENGINE_API Level
{
public:
	Level();
	virtual ~Level();

	// 액터 추가 함수
	void AddActor(Actor* newActor);			// 레벨에 액터를 추가하는 함수

	// 루프 처리 함수
	virtual void Update(float deltaTime);	// 레벨에 액터를 업데이트하는 함수
	virtual void Draw();					// 레벨에 액터를 렌더링하는 함수

private:
	// 게임 공간에 배치되는 액터 배열 (Actor*의 배열)
	// 프로그램 실행 중에 배열의 크기를 동적으로 변경하려면 이중 포인터가 필요함
	Actor** actors;

	// 배열의 최대 크기 (저장 가능한 액터의 수)
	int capacity;

	// 현재 배열에 저장된 액터의 수
	int count;
};
