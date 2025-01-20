#include "GameLevel.h"
#include "Engine/Engine.h"
#include "Game/Game.h"

#include "Actor/Player.h"
#include "Actor/EnemyA.h"
#include "Actor/EnemyB.h"
#include "Actor/EnemyBullet.h"
#include "Actor/EnemyC.h"

GameLevel::GameLevel()
	: player(new Player("P"))
{
	AddActor(player);

	// EnemyA ���� �� 1�ʺ��� ����
	spawnIntervalA = 1.0f;

	// EnemyB ���� �� 5�ʺ��� ����
	spawnIntervalB = 5.0f;

	// EnemyC ���� �� 10�ʺ��� ����
	spawnIntervalC = 10.0f;
}

void GameLevel::Update(float deltaTime)
{
	Super::Update(deltaTime);

	if (Engine::Get().GetKeyDown(VK_ESCAPE))
	{
		Game::Get().ToggleLevel("Game Menu");
	}

	// EnemyA ��ȯ Ÿ�̸� ������Ʈ
	spawnElapsedTimeA += deltaTime;
	if (spawnElapsedTimeA >= spawnIntervalA)
	{
		spawnElapsedTimeA = 0.0f;
		spawnIntervalA = RandomPercent(0.1f, 1.0f); // ���ο� ���� ��ȯ ���� ����
		SpawnEnemyA(); // EnemyA ��ȯ
	}

	// EnemyB ��ȯ Ÿ�̸� ������Ʈ
	spawnElapsedTimeB += deltaTime;
	if (spawnElapsedTimeB >= spawnIntervalB)
	{
		spawnElapsedTimeB = 0.0f;
		spawnIntervalB = RandomPercent(0.5f, 2.0f); // ���ο� ���� ��ȯ ���� ����
		SpawnEnemyB(); // EnemyB ��ȯ
	}

	// EnemyC ��ȯ Ÿ�̸� ������Ʈ
	spawnElapsedTimeC += deltaTime;
	if (spawnElapsedTimeC >= spawnIntervalC)
	{
		spawnElapsedTimeC = 0.0f;
		spawnIntervalC = RandomPercent(1.0f, 3.0f); // ���ο� ���� ��ȯ ���� ����
		SpawnEnemyC(); // EnemyC ��ȯ
	}

	ProcessCollisionPlayerAndEnemyA();
	ProcessCollisionPlayerAndEnemyB();
	ProcessCollisionPlayerAndBullet();
	ProcessCollisionPlayerAndEnemyC();
}

void GameLevel::Draw()
{
	// �׵θ� �׸���
	DrawBorder();

	// ���� �׸���
	for (Actor* actor : actors)
	{
		actor->Draw();
	}
}

Player* GameLevel::GetPlayer() const
{
	return player;
}

void GameLevel::DrawBorder()
{
	// ȭ�� ũ�� ��������
	Vector2 screenSize = Engine::Get().ScreenSize();

	// ���ʰ� �Ʒ��� �׵θ�
	for (int x = 0; x < screenSize.x; ++x)
	{
		// ���� �׵θ�
		Engine::Get().Draw(Vector2(x, 0), "-", Color::White);

		// �Ʒ��� �׵θ�
		Engine::Get().Draw(Vector2(x, screenSize.y - 1), "-", Color::White);
	}

	// ���ʰ� ������ �׵θ�
	for (int y = 0; y < screenSize.y; ++y)
	{
		// ���� �׵θ�
		Engine::Get().Draw(Vector2(0, y), "|", Color::White);

		// ������ �׵θ�
		Engine::Get().Draw(Vector2(screenSize.x - 1, y), "|", Color::White);
	}
}

void GameLevel::SpawnEnemyA()
{
	float enemySpeedA = RandomPercent(10.0f, 15.0f);
	AddActor(new EnemyA("A", enemySpeedA));
}

void GameLevel::SpawnEnemyB()
{
	float enemySpeedB = RandomPercent(3.0f, 5.0f);
	SpawnPosition spawnPosition = static_cast<SpawnPosition>(Random(0, 3));
	AddActor(new EnemyB("B", spawnPosition, enemySpeedB));
}

void GameLevel::SpawnEnemyC()
{
	float enemySpeedC = RandomPercent(5.0f, 10.0f);
	AddActor(new EnemyC("C", enemySpeedC));
}

void GameLevel::ProcessCollisionPlayerAndEnemyA()
{
	// Player�� EnemyA �迭 ����
	Player* player = nullptr;
	List<EnemyA*> enemyAs;

	// ������ ��ġ�� ���͸� ��ȸ�ϸ鼭 ����Ʈ ä���
	for (Actor* actor : actors)
	{
		// �÷��̾� �˻�
		if (!player)
		{
			player = actor->As<Player>();
			continue;
		}

		// EnemyA�� �� ��ȯ �� Ȯ���ؼ� ����Ʈ ä���
		EnemyA* enemyA = actor->As<EnemyA>();
		if (enemyA)
		{
			enemyAs.PushBack(enemyA);
			continue;
		}
	}

	// ���� ó��
	if (player == nullptr || enemyAs.Size() == 0)
	{
		return;
	}

	// �迭�� ��ȸ�ϸ鼭 �浹 ó��
	for (EnemyA* enemyA : enemyAs)
	{
		// Player�� EnemyA�� �浹�ߴ��� Ȯ��
		if (player->Intersect(*enemyA))
		{
			// �÷��̾� ���
			player->Destroy();

			// �� 2�ʰ� ����
			Sleep(2000);

			// ���� ����
			Engine::Get().QuitGame();
		}
	}
}

void GameLevel::ProcessCollisionPlayerAndEnemyB()
{
	// Player�� EnemyB �迭 ����
	Player* player = nullptr;
	List<EnemyB*> enemyBs;

	// ������ ��ġ�� ���͸� ��ȸ�ϸ鼭 ����Ʈ ä���
	for (Actor* actor : actors)
	{
		// �÷��̾� �˻�
		if (!player)
		{
			player = actor->As<Player>();
			continue;
		}

		// EnemyB�� �� ��ȯ �� Ȯ���ؼ� ����Ʈ ä���
		EnemyB* enemyB = actor->As<EnemyB>();
		if (enemyB)
		{
			enemyBs.PushBack(enemyB);
			continue;
		}
	}

	// ���� ó��
	if (player == nullptr || enemyBs.Size() == 0)
	{
		return;
	}

	// �迭�� ��ȸ�ϸ鼭 �浹 ó��
	for (EnemyB* enemyB : enemyBs)
	{
		// Player�� EnemyB�� �浹�ߴ��� Ȯ��
		if (player->Intersect(*enemyB))
		{
			// �÷��̾� ���
			player->Destroy();

			// �� 2�ʰ� ����
			Sleep(2000);

			// ���� ����
			Engine::Get().QuitGame();
		}
	}
}

void GameLevel::ProcessCollisionPlayerAndBullet()
{
	// �÷��̾�� �� ź�� ���� ����
	Player* player = nullptr;
	List<EnemyBullet*> bullets;

	// ������ ��ġ�� ���͸� ��ȸ�ϸ鼭 ����Ʈ ä���
	for (Actor* actor : actors)
	{
		// �÷��̾� �˻�
		if (!player)
		{
			player = actor->As<Player>();
			continue;
		}

		// ź������ �� ��ȯ �� Ȯ���ؼ� ����Ʈ ä���
		EnemyBullet* bullet = actor->As<EnemyBullet>();
		if (bullet)
		{
			bullets.PushBack(bullet);
			continue;
		}
	}

	// ���� ó��
	if (player == nullptr || bullets.Size() == 0)
	{
		return;
	}

	// �迭�� ��ȸ�ϸ鼭 �浹 ó��
	for (EnemyBullet* bullet : bullets)
	{
		// ź��� �÷��̾ �浹�ߴ� Ȯ��
		if (player->Intersect(*bullet))
		{
			// �÷��̾� ���
			player->Destroy();

			// �� 2�ʰ� ����
			Sleep(2000);

			// ���� ����
			Engine::Get().QuitGame();
		}
	}
}

void GameLevel::ProcessCollisionPlayerAndEnemyC()
{
	// Player�� EnemyC �迭 ����
	Player* player = nullptr;
	List<EnemyC*> enemyCs;

	// ������ ��ġ�� ���͸� ��ȸ�ϸ鼭 ����Ʈ ä���
	for (Actor* actor : actors)
	{
		// �÷��̾� �˻�
		if (!player)
		{
			player = actor->As<Player>();
			continue;
		}

		// EnemyC�� �� ��ȯ �� Ȯ���ؼ� ����Ʈ ä���
		EnemyC* enemyC = actor->As<EnemyC>();
		if (enemyC)
		{
			enemyCs.PushBack(enemyC);
			continue;
		}
	}

	// ���� ó��
	if (player == nullptr || enemyCs.Size() == 0)
	{
		return;
	}

	// �迭�� ��ȸ�ϸ鼭 �浹 ó��
	for (EnemyC* enemyC : enemyCs)
	{
		// Player�� EnemyC�� �浹�ߴ��� Ȯ��
		if (player->Intersect(*enemyC))
		{
			// �÷��̾� ���
			player->Destroy();

			// �� 2�ʰ� ����
			Sleep(2000);

			// ���� ����
			Engine::Get().QuitGame();
		}
	}
}
