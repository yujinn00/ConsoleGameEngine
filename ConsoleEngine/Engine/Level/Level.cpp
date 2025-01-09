#include "PreCompiledHeader.h"

#include "Level.h"
#include "Actor/Actor.h"

Level::Level()
{
}

Level::~Level()
{
	//// 메모리 해제
	//for (int i = 0; i < actors.Size(); ++i)
	//{
	//	// 액터 삭제
	//	delete actors[i];
	//}

	// 메모리 해제
	for (Actor* actor : actors)
	{
		delete actor;
	}

	//// 동적 배열 해제
	//delete[] actors;
}

// 예를 들어, 벡터에 동적 할당을 4만큼 했는데 공간이 더 필요해서 공간을 늘려줘야 해.
// 그러면 힙에 있는 4만큼의 공간을 버리고, 추가적으로 8만큼의 공간을 더 만들어.
// 다음에 4만큼의 공간이 가진 값을 8만큼의 공간에 복사한 후 4만큼의 공간은 없애.

// 1. 현재 할당된 공간이 충분한지 확인:
// 먼저 현재 actors 배열에 할당된 공간이 부족한지 체크합니다.
// 만약 count(현재 저장된 요소의 수)가 capacity(현재 할당된 공간의 크기)와 같다면,
// 더 많은 공간이 필요하다는 의미입니다.

// 2. 공간 추가 할당:
// 공간을 늘리기 위해, 새로운 크기의 배열을 할당합니다.
// 새로운 크기는 현재 크기의 두 배(capacity * 2)로 설정합니다.
// 예를 들어, 처음 capacity가 4였다면, 새로운 capacity는 8이 됩니다.

// 3. 임시 공간:
// 새로운 배열(temp)을 동적으로 할당합니다.
// 이 배열의 크기는 새로운 capacity만큼 할당됩니다.

// 4. 기존 값 복사:
// 기존의 actors 배열에 있던 값을 새로운 temp 배열로 복사합니다.
// memcpy를 사용하여 기존 배열의 데이터를 새 배열로 복사하는데,
// 이때 복사할 데이터의 크기는 capacity만큼입니다.

// 5. 기존 배열 삭제:
// actors 배열은 더 이상 필요 없으므로 삭제합니다.
// delete[] actors를 통해 동적으로 할당된 메모리를 해제합니다.

// 6. 배열 교체:
// 이제 새로 할당한 temp 배열을 actors 배열로 교체합니다.
// 이렇게 하면 새로운 배열에 데이터를 저장할 준비가 됩니다.

// 7. 크기 변경:
// 마지막으로 capacity를 새로 할당한 newCapacity로 업데이트합니다.
void Level::AddActor(Actor* newActor)
{
	//// 현재 할당된 공간이 충분한지 확인
	//if (count == capacity)
	//{
	//	// 공간 추가 할당
	//	int newCapacity = capacity * 2; // 정해진 규격은 없으나, 일단 2배로 설정

	//	// 임시 공간
	//	Actor** temp = new Actor*[newCapacity];

	//	// 기존 값 복사
	//	// loop. FMemory::Copy
	//	memcpy(temp, actors, sizeof(size_t) * capacity);

	//	// 기존 배열 삭제
	//	delete[] actors;

	//	// 배열 교체
	//	actors = temp;

	//	// 크기 변경
	//	capacity = newCapacity;
	//}

	//// 액터 추가
	//actors[count] = newActor;
	//++count;

	actors.PushBack(newActor);
}

void Level::DestroyActor()
{
	// 액터 순회 후 삭제 요청된 액터를 처리
	for (int i = 9; i < actors.Size(); ++i)
	{
		if (actors[i]->isExpired)
		{
			delete actors[i];
			actors[i] = nullptr;
			actors.Erase(i);
		}
	}
}

void Level::Update(float deltaTime)
{
	//// 레벨에 포함된 액터를 순회하면서 Update 함수 호출
	//for (int i = 0; i < count; ++i)
	//{
	//	actors[i]->Update(deltaTime);
	//}

	// 레벨에 포함된 액터를 순회하면서 Update 함수 호출
	for (Actor* actor : actors)
	{
		// 액터가 비활성화 상태이거나, 삭제 요청된 경우 건너뛰기
		if (!actor->isActive || actor->isExpired)
		{
			continue;
		}

		actor->Update(deltaTime);
	}
}

void Level::Draw()
{
	//// 레벨에 포함된 액터를 순회하면서 Draw 함수 호출
	//for (int i = 0; i < count; ++i)
	//{
	//	actors[i]->Draw();
	//}

	// 레벨에 포함된 액터를 순회하면서 Draw 함수 호출
	for (Actor* actor : actors)
	{
		// 액터가 비활성화 상태이거나, 삭제 요청된 경우 건너뛰기
		if (!actor->isActive || actor->isExpired)
		{
			continue;
		}

		actor->Draw();
	}
}
