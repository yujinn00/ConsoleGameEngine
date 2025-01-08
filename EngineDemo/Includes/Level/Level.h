#pragma once

#include "Core.h"
#include "RTTI.h"
#include "Container/List.h"

// 전방 선언
class Actor;

class ENGINE_API Level : public RTTI
{
	// RTTI 정의
	RTTI_DECLARATIONS(Level, RTTI)

public:
	Level();
	virtual ~Level();

	// 액터 추가 함수
	void AddActor(Actor* newActor);

	// 루프 처리 함수
	virtual void Update(float deltaTime);
	virtual void Draw();

protected:
	// 게임 공간에 배치되는 물체(액터) 배열
	List<Actor*> actors;

	//// 게임 공간에 배치되는 물체(액터) 배열
	//Actor** actors;

	//// 저장할 수 있는 공간의 크기
	//int capacity;

	//// 액터의 수
	//int count;
};
