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

void Level::AddActor(Actor* newActor)
{
	addRequestedActors.push_back(newActor); // ��û�� ���͸� ����Ʈ�� �߰�
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
	for (Actor* actor : addRequestedActors)
	{
		actors.PushBack(actor);
	}

	// �߰� ��û ����Ʈ �ʱ�ȭ
	addRequestedActors.clear();
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
