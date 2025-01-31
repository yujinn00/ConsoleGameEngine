#include "GameLevel.h"
#include "Engine/Engine.h"

#include "Actor/Wall.h"
#include "Actor/Ground.h"
#include "Actor/Box.h"
#include "Actor/Target.h"
#include "Actor/Player.h"

#include "Engine/Timer.h"

GameLevel::GameLevel()
{
	// Ŀ�� ���߱�
	Engine::Get().SetCursorType(CursorType::NoCursor);

	// �� ���� �ҷ��� ���� �ε�
	// ���� �б�
	FILE* file = nullptr;
	fopen_s(&file, "../Assets/Maps/Stage3.txt", "rb");

	// ���� ó��
	if (file == nullptr)
	{
		std::cout << "�� ���� ���� ����\n";
		__debugbreak();
		return;
	}

	// ���� �б�
	// �� ��ġ�� �̵�
	fseek(file, 0, SEEK_END);

	// �̵��� ��ġ�� FP ��������
	size_t readSize = ftell(file);

	// FP ����ġ
	rewind(file);

	// ���� �о ���ۿ� ���
	char* buffer = new char[readSize + 1];
	size_t bytesRead = fread(buffer, 1, readSize, file);

	if (readSize != bytesRead)
	{
		std::cout << "�о�� ũ�Ⱑ �ٸ�\n";
		__debugbreak();
		return;
	}

	buffer[readSize] = '\0';

	// ���� ���� �� ����� �ε���
	int index = 0;

	// ��ǥ ����� ���� ���� ����
	int xPosition = 0;
	int yPosition = 0;

	// �ؼ� (�Ľ�)
	while (index < (int)bytesRead)
	{
		// �� ���ھ� �б�
		char mapChar = buffer[index++];

		// ���� ������ ��� ó��
		if (mapChar == '\n')
		{
			++yPosition;
			xPosition = 0;
			continue;
		}

		// �� ���ڰ� 1�̸� Wall ���� ����
		if (mapChar == '1')
		{
			Wall* wall = new Wall(Vector2(xPosition, yPosition));
			actors.PushBack(wall);
			map.PushBack(wall);
		}

		// �� ���ڰ� .�̸� �׶��� ���� ����
		else if (mapChar == '.')
		{
			Ground* ground = new Ground(Vector2(xPosition, yPosition));
			actors.PushBack(ground);
			map.PushBack(ground);
		}

		// �� ���ڰ� b�̸� �ڽ� ���� ����
		else if (mapChar == 'b')
		{
			// 1. �׶��带 ���� �׸���.
			Ground* ground = new Ground(Vector2(xPosition, yPosition));
			actors.PushBack(ground);
			map.PushBack(ground);

			// 2. �ڽ��� �����.
			Box* box = new Box(Vector2(xPosition, yPosition));
			actors.PushBack(box);
			boxes.PushBack(box);	
		}

		// �� ���ڰ� t�̸� Ÿ�� ���� ����
		else if (mapChar == 't')
		{
			Target* target = new Target(Vector2(xPosition, yPosition));
			actors.PushBack(target);
			map.PushBack(target);
			targets.PushBack(target);
		}

		// �� ���ڰ� p�̸� �÷��̾� ���� ����
		else if (mapChar == 'p')
		{
			// 1. �׶��带 ���� �׸���.
			Ground* ground = new Ground(Vector2(xPosition, yPosition));
			actors.PushBack(ground);
			map.PushBack(ground);

			// 2. �÷��̾�� �����.
			player = new Player(Vector2(xPosition, yPosition), this);
			actors.PushBack(player);
		}

		++xPosition;
	}

	// ���� ����
	delete[] buffer;

	// ���� �ݱ�
	fclose(file);
}

void GameLevel::Update(float deltaTime)
{
	Super::Update(deltaTime);

	// ������ Ŭ���������, ���� ���� ó��
	if (isGameClear)
	{
		// Ÿ�̸� (�뷫 �� ������ ������ �ð� ���)
		static Timer timer(0.1f);
		timer.Update(deltaTime);
		if (!timer.IsTimeOut())
		{
			return;
		}

		// Ŀ�� �̵�
		Engine::Get().SetCursorPosition(0, Engine::Get().ScreenSize().y);

		// �޼��� ���
		Log("Game Clear!");

		// ������ ����
		Sleep(2000);

		// ���� ���� ó��
		Engine::Get().QuitGame();
	}
}

void GameLevel::Draw()
{
	// 1. �� �׸���
	for (auto* actor : map)
	{
		// �÷��̾� ��ġ Ȯ��
		if (actor->GetPosition() == player->GetPosition())
		{
			continue;
		}

		// �ڽ� ��ġ Ȯ��
		bool shouldDraw = true;
		for (auto* box : boxes)
		{
			if (actor->GetPosition() == box->GetPosition())
			{
				shouldDraw = false;
				break;
			}
		}

		// �� ���� �׸���
		if (shouldDraw)
		{
			actor->Draw();
		}
	}

	// 2. Ÿ�� �׸���
	for (auto* target : targets)
	{
		// �÷��̾� ��ġ Ȯ��
		if (target->GetPosition() == player->GetPosition())
		{
			continue;
		}

		// �ڽ� ��ġ Ȯ��
		bool shouldDraw = true;
		for (auto* box : boxes)
		{
			if (target->GetPosition() == box->GetPosition())
			{
				shouldDraw = false;
				break;
			}
		}

		// Ÿ�� ���� �׸���
		if (shouldDraw)
		{
			target->Draw();
		}
	}

	// 3. �ڽ� �׸���
	for (auto* box : boxes)
	{
		// �ڽ� ���� �׸���
		box->Draw();
	}

	// 4. �÷��̾� �׸���
	player->Draw();
}

bool GameLevel::canPlayerMove(const Vector2& position)
{
	// ������ Ŭ����� ��� �ٷ� ����
	if (isGameClear) 
	{
		return false;
	}

	// �ڽ� �˻�
	Box* searchedBox = nullptr;
	for (auto* box : boxes)
	{
		if (box->GetPosition() == position)
		{
			searchedBox = box;
			break;
		}
	}

	// �ڽ��� ���� �� ó��
	if (searchedBox)
	{
		// �̵� ����
		int directionX = position.x - player->GetPosition().x;
		int directionY = position.y - player->GetPosition().y;

		// �ڽ��� �̵��� �� ��ġ
		Vector2 newPosition = searchedBox->GetPosition() + Vector2(directionX, directionY);

		// �߰� �˻� (�ڽ�)
		for (auto* box : boxes)
		{
			// ���� ó��
			if (box == searchedBox)
			{
				continue;
			}

			// �̵��� ��ġ�� �ٸ� �ڽ��� �ִٸ� �̵� �Ұ�
			if (box->GetPosition() == newPosition)
			{
				return false;
			}
		}

		// �߰� �˻� (��)
		for (auto* actor : map)
		{
			// �̵��Ϸ��� ��ġ�� �ִ� ���� �˻�
			if (actor->GetPosition() == newPosition)
			{
				// �� ��ȯ�� ���� ��ü�� Ÿ�� Ȯ��
				// �̵��Ϸ��� ��ġ�� ���� ������ �̵� �Ұ�
				if (actor->As<Wall>())
				{
					return false;
				}

				// �� ��ȯ�� ���� ��ü�� Ÿ�� Ȯ��
				// ���̳� Ÿ���̸� �̵� ����
				if (actor->As<Ground>() || actor->As<Target>())
				{
					// �ڽ� �̵� ó��
					searchedBox->SetPosition(newPosition);

					// ���� Ŭ���� ���� Ȯ��
					isGameClear = CheckGameClear();

					return true;
				}
			}
		}
	}

	// �̵��Ϸ��� ��ġ�� ���� �ִ��� Ȯ��
	DrawableActor* searchedActor = nullptr;
	for (auto* actor : map)
	{
		if (actor->GetPosition() == position)
		{
			searchedActor = actor;
			break;
		}
	}

	// �˻��� ���Ͱ� ������ Ȯ��
	if (searchedActor->As<Wall>())
	{
		return false;
	}

	// �˻��� ���Ͱ� �̵� ������ ����(��/Ÿ��)���� Ȯ��
	if (searchedActor->As<Ground>() || searchedActor->As<Target>())
	{
		return true;
	}

	return false;
}

bool GameLevel::CheckGameClear()
{
	// ���� Ȯ���� ���� ����
	int currentScore = 0;
	int targetScore = targets.Size();

	// Ÿ�� ��ġ�� ��ġ�� �ڽ� ���� ����
	for (auto* box : boxes)
	{
		for (auto* target : targets)
		{
			// ���� Ȯ��
			if (box->GetPosition() == target->GetPosition())
			{
				++currentScore;
				continue;
			}
		}
	}

	// ȹ���� ������ ��ǥ ������ ������ ��
	return currentScore == targetScore;
}
