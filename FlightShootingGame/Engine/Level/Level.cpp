#include "PreCompiledHeader.h"

#include "Level.h"
#include "Actor/Actor.h"

Level::Level()
{
}

Level::~Level()
{
	// �޸� ����
	for (Actor* actor : actors)
	{
		delete actor;
	}
}

// ���� ���, ���Ϳ� ���� �Ҵ��� 4��ŭ �ߴµ� ������ �� �ʿ��ؼ� ������ �÷���� ��.
// �׷��� ���� �ִ� 4��ŭ�� ������ ������, �߰������� 8��ŭ�� ������ �� �����.
// ������ 4��ŭ�� ������ ���� ���� 8��ŭ�� ������ ������ �� 4��ŭ�� ������ ����.

// 1. ���� �Ҵ�� ������ ������� Ȯ��:
// ���� ���� actors �迭�� �Ҵ�� ������ �������� üũ�մϴ�.
// ���� count(���� ����� ����� ��)�� capacity(���� �Ҵ�� ������ ũ��)�� ���ٸ�,
// �� ���� ������ �ʿ��ϴٴ� �ǹ��Դϴ�.

// 2. ���� �߰� �Ҵ�:
// ������ �ø��� ����, ���ο� ũ���� �迭�� �Ҵ��մϴ�.
// ���ο� ũ��� ���� ũ���� �� ��(capacity * 2)�� �����մϴ�.
// ���� ���, ó�� capacity�� 4���ٸ�, ���ο� capacity�� 8�� �˴ϴ�.

// 3. �ӽ� ����:
// ���ο� �迭(temp)�� �������� �Ҵ��մϴ�.
// �� �迭�� ũ��� ���ο� capacity��ŭ �Ҵ�˴ϴ�.

// 4. ���� �� ����:
// ������ actors �迭�� �ִ� ���� ���ο� temp �迭�� �����մϴ�.
// memcpy�� ����Ͽ� ���� �迭�� �����͸� �� �迭�� �����ϴµ�,
// �̶� ������ �������� ũ��� capacity��ŭ�Դϴ�.

// 5. ���� �迭 ����:
// actors �迭�� �� �̻� �ʿ� �����Ƿ� �����մϴ�.
// delete[] actors�� ���� �������� �Ҵ�� �޸𸮸� �����մϴ�.

// 6. �迭 ��ü:
// ���� ���� �Ҵ��� temp �迭�� actors �迭�� ��ü�մϴ�.
// �̷��� �ϸ� ���ο� �迭�� �����͸� ������ �غ� �˴ϴ�.

// 7. ũ�� ����:
// ���������� capacity�� ���� �Ҵ��� newCapacity�� ������Ʈ�մϴ�.

//void Level::AddActor(Actor* newActor)
//{
//	// ���� �Ҵ�� ������ ������� Ȯ��
//	if (count == capacity)
//	{
//		// ���� �߰� �Ҵ�
//		int newCapacity = capacity * 2; // ������ �԰��� ������, �ϴ� 2��� ����
//
//		// �ӽ� ����
//		Actor** temp = new Actor * [newCapacity];
//
//		// ���� �� ����
//		// loop. FMemory::Copy
//		memcpy(temp, actors, sizeof(size_t) * capacity);
//
//		// ���� �迭 ����
//		delete[] actors;
//
//		// �迭 ��ü
//		actors = temp;
//
//		// ũ�� ����
//		capacity = newCapacity;
//	}
//
//	// ���� �߰�
//	actors[count] = newActor;
//	++count;
//}

void Level::AddActor(Actor* newActor)
{
	addRequestedActor = newActor;
}

void Level::ProcessAddedAndDestroyedActor()
{
	// ���� ��ȸ �� ���� ��û�� ���͸� ó��
	for (int i = 0; i < actors.Size();)
	{
		if (actors[i]->isExpired)
		{
			delete actors[i];
			actors[i] = nullptr;
			actors.Erase(i);
			continue;
		}

		++i;
	}

	// �߰� ��û�� ���� ó��
	if (addRequestedActor)
	{
		actors.PushBack(addRequestedActor);
		addRequestedActor = nullptr;
	}
}

void Level::Update(float deltaTime)
{
	// ������ ���Ե� ���͸� ��ȸ�ϸ鼭 Update �Լ� ȣ��
	for (Actor* actor : actors)
	{
		// ���Ͱ� ��Ȱ��ȭ �����̰ų�, ���� ��û�� ��� �ǳʶٱ�
		if (!actor->isActive || actor->isExpired)
		{
			continue;
		}

		actor->Update(deltaTime);
	}
}

void Level::Draw()
{
	// ������ ���Ե� ���͸� ��ȸ�ϸ鼭 Draw �Լ� ȣ��
	for (Actor* actor : actors)
	{
		// ���Ͱ� ��Ȱ��ȭ �����̰ų�, ���� ��û�� ��� �ǳʶٱ�
		if (!actor->isActive || actor->isExpired)
		{
			continue;
		}

		actor->Draw();
	}
}
