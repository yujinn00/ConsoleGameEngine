#include "PreCompiledHeader.h"

#include "Level.h"
#include "Actor/Actor.h"
#include <iostream>

Level::Level()
	: actors(nullptr), capacity(4), count(0)
{
	// 동적으로 Actor* 배열 생성
	actors = new Actor*[capacity];

	// 배열의 값을 0으로 초기화
	memset(actors, 0, sizeof(size_t) * capacity);
}

Level::~Level()
{
	// 배열에 저장된 모든 액터 삭제
	for (int i = 0; i < count; ++i)
	{
		delete actors[i]; // 각 액터 삭제
	}

	// 동적 배열 자체 삭제
	delete[] actors;
}

void Level::AddActor(Actor* newActor)
{
	// 배열이 꽉 찬 경우 배열의 크기를 두 배로 확장
	if (count == capacity)
	{
		int newCapacity = capacity * 2; // 새로운 크기 설정
		Actor** temp = new Actor*[newCapacity];

		// 기존 배열의 내용을 새 배열로 복사
		memcpy(temp, actors, sizeof(size_t) * capacity);

		// 기존 배열 삭제
		delete[] actors;

		// 배열 교체 및 크기 갱신
		actors = temp;
		capacity = newCapacity;
	}

	// 새 액터를 배열에 추가
	actors[count] = newActor;
	++count; // 액터 수 증가
}

void Level::Update(float deltaTime)
{
	// 모든 액터에 대해 업데이트 호출
	for (int i = 0; i < count; ++i)
	{
		actors[i]->Update(deltaTime); // 액터의 상태 갱신
	}
}

void Level::Draw()
{
	// 모든 액터에 대해 렌더링 호출
	for (int i = 0; i < count; ++i)
	{
		actors[i]->Draw(); // 액터를 화면에 렌더링
	}
}
