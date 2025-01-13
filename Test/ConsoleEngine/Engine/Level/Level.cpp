#include "PreCompiledHeader.h"

#include "Level.h"
#include "Actor/Actor.h"
#include <iostream>

Level::Level()
	: actors(nullptr), capacity(4), count(0)
{
	// �������� Actor* �迭 ����
	actors = new Actor*[capacity];

	// �迭�� ���� 0���� �ʱ�ȭ
	memset(actors, 0, sizeof(size_t) * capacity);
}

Level::~Level()
{
	// �迭�� ����� ��� ���� ����
	for (int i = 0; i < count; ++i)
	{
		delete actors[i]; // �� ���� ����
	}

	// ���� �迭 ��ü ����
	delete[] actors;
}

void Level::AddActor(Actor* newActor)
{
	// �迭�� �� �� ��� �迭�� ũ�⸦ �� ��� Ȯ��
	if (count == capacity)
	{
		int newCapacity = capacity * 2; // ���ο� ũ�� ����
		Actor** temp = new Actor*[newCapacity];

		// ���� �迭�� ������ �� �迭�� ����
		memcpy(temp, actors, sizeof(size_t) * capacity);

		// ���� �迭 ����
		delete[] actors;

		// �迭 ��ü �� ũ�� ����
		actors = temp;
		capacity = newCapacity;
	}

	// �� ���͸� �迭�� �߰�
	actors[count] = newActor;
	++count; // ���� �� ����
}

void Level::Update(float deltaTime)
{
	// ��� ���Ϳ� ���� ������Ʈ ȣ��
	for (int i = 0; i < count; ++i)
	{
		actors[i]->Update(deltaTime); // ������ ���� ����
	}
}

void Level::Draw()
{
	// ��� ���Ϳ� ���� ������ ȣ��
	for (int i = 0; i < count; ++i)
	{
		actors[i]->Draw(); // ���͸� ȭ�鿡 ������
	}
}
