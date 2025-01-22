#include "GameLevel.h"
#include "Engine/Engine.h"
#include "Game/Game.h"

#include "Actor/Player/Player.h"
#include "Actor/Player/PlayerBullet.h"

#include "Actor/Enemy/EnemyA.h"
#include "Actor/Enemy/EnemyB.h"
#include "Actor/Enemy/EnemyC.h"
#include "Actor/Enemy/EnemyBullet.h"

#include "Actor/Item/Bomb.h"
#include "Actor/Item/Shield.h"
#include "Actor/Item/Upgrade.h"

#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

GameLevel::GameLevel()
	: player(new Player("P"))
{
	AddActor(player);
}

void GameLevel::Update(float deltaTime)
{
	Super::Update(deltaTime);

	if (Engine::Get().GetKeyDown(VK_ESCAPE))
	{
		Game::Get().ToggleLevel("Game Menu");
	}

	// ���� Ÿ�̸� ������Ʈ
	ElapsedTime += deltaTime;
	spawnElapsedTimeA += deltaTime;
	spawnElapsedTimeB += deltaTime;
	spawnElapsedTimeC += deltaTime;
	scoreUpdateElapsedTime += deltaTime;

	// 1�ʸ��� ���� ������Ʈ
	if (scoreUpdateElapsedTime >= 1.0f)
	{
		if (ElapsedTime < 20.0f)
		{
			score += 1;
		}
		else if (ElapsedTime >= 20.0f && ElapsedTime < 40.0f)
		{
			score += 2;
		}
		else if (ElapsedTime >= 40.0f && ElapsedTime < 60.0f)
		{
			score += 3;
		}

		scoreUpdateElapsedTime = 0.0f; // Ÿ�̸� �ʱ�ȭ
	}

	// ������ ���� �� �ű� ���� ����
	if (ElapsedTime < 20.0f)
	{
		if (spawnElapsedTimeA >= spawnIntervalA)
		{
			spawnElapsedTimeA = 0.0f;
			spawnIntervalA = RandomPercent(0.1f, 0.3f); // ���ο� ���� ��ȯ ���� ����
			SpawnEnemyA(); // EnemyA ��ȯ
		}
	}
	else if (ElapsedTime >= 20.0f && ElapsedTime < 40.0f)
	{
		if (spawnElapsedTimeB >= spawnIntervalB)
		{
			spawnElapsedTimeB = 0.0f;
			spawnIntervalB = RandomPercent(0.5f, 1.0f); // ���ο� ���� ��ȯ ���� ����
			SpawnEnemyB(); // EnemyB ��ȯ
		}
	}
	else if (ElapsedTime >= 40.0f && ElapsedTime < 60.0f)
	{
		if (spawnElapsedTimeC >= spawnIntervalC)
		{
			spawnElapsedTimeC = 0.0f;
			spawnIntervalC = RandomPercent(0.3f, 0.5f); // ���ο� ���� ��ȯ ���� ����
			SpawnEnemyC(); // EnemyC ��ȯ
		}
	}

	// ������ ���� �� ���� ���� ����
	if (ElapsedTime >= 20.0f && !isRemovedEnemyA)
	{
		// �ʿ� �ִ� EnemyA �� ���׷��̵� ������ ����
		for (Actor* actor : actors)
		{
			if (actor->As<EnemyA>() || actor->As<Upgrade>())
			{
				actor->Destroy();
			}
		}

		// EnemyA ���� ���� �Ϸ�
		isRemovedEnemyA = true;
	}
	else if (ElapsedTime >= 40.0f && !isRemovedEnemyB)
	{
		// �ʿ� �ִ� EnemyB(ź�� ����) �� ���׷��̵� ������ ����
		for (Actor* actor : actors)
		{
			if (actor->As<EnemyB>() || actor->As<EnemyBullet>() || actor->As<Upgrade>())
			{
				actor->Destroy();
			}
		}

		// EnemyB ���� ���� �Ϸ�
		isRemovedEnemyB = true;
	}
	else if (ElapsedTime >= 60.0f && !isRemovedEnemyC)
	{
		// �ʿ� �ִ� EnemyC �� ���׷��̵� ������ ����
		for (Actor* actor : actors)
		{
			if (actor->As<EnemyC>() || actor->As<Upgrade>())
			{
				actor->Destroy();
			}
		}

		// @Todo: ������ �ִ��� �����Ŀ� ���� �Ʒ� bool�̶� ���߿� �÷��̾� destroy�� �ϰų� ���ؾ� �� !!
		// �ٵ� �� �÷��̾� ���� ���ص� �޸� ���� �ȳ��� ?
		// EnemyC ���� ���� �Ϸ�
		isRemovedEnemyC = true;

		// �� 2�ʰ� ����
		Sleep(2000);

		// ���� ������ ���Ͽ� ����
		SaveScore(score);

		// ���� ����
		Engine::Get().QuitGame();
	}

	// ������ ����
	if (ElapsedTime < 60.0f)
	{
		// ��ź ������ ����
		spawnElapsedTimeBomb += deltaTime;
		if (spawnElapsedTimeBomb >= spawnIntervalBomb)
		{
			spawnElapsedTimeBomb = 0.0f;
			spawnIntervalBomb = RandomPercent(5.0f, 10.0f); // ���ο� ���� ��ȯ ���� ����
			SpawnBomb(); // Bomb ��ȯ
		}

		// ���� ������ ����
		if (ElapsedTime < 120.0f)
		{
			spawnElapsedTimeShield += deltaTime;
			if (spawnElapsedTimeShield >= spawnIntervalShield)
			{
				spawnElapsedTimeShield = 0.0f;
				spawnIntervalShield = RandomPercent(5.0f, 10.0f); // ���ο� ���� ��ȯ ���� ����
				SpawnShield(); // Shield ��ȯ
			}
		}

		// ���׷��̵� ������ ����
		spawnElapsedTimeUpgrade += deltaTime;
		if (spawnElapsedTimeUpgrade >= spawnIntervalUpgrade)
		{
			spawnElapsedTimeUpgrade = 0.0f;
			spawnIntervalUpgrade = 20.0f; // ��ȯ ���� 20�� ����
			SpawnUpgrade(); // Upgrade ��ȯ
		}
	}

	// �浹 ó�� �Լ� ȣ��
	ProcessCollisionPlayerAndEnemyA();
	ProcessCollisionPlayerAndEnemyB();
	ProcessCollisionPlayerAndEnemyC();
	ProcessCollisionPlayerAndBullet();
	ProcessCollisionEnemyAndBullet();
	ProcessCollisionPlayerAndBomb();
	ProcessCollisionPlayerAndShield();
	ProcessCollisionPlayerAndUpgrade();
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

	// ���� ����ϱ�
	std::string scoreText = "Score: " + std::to_string(score);
	Engine::Get().Draw(Vector2(Engine::Get().ScreenSize().x / 2 - 5, 0), scoreText.c_str(), Color::Green);
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

Player* GameLevel::GetPlayer() const
{
	return player;
}

void GameLevel::SaveScore(int score)
{
	std::vector<int> scores;

	// ���Ͽ��� ���� ���� �б�
	std::ifstream fin("Rank.txt");
	if (fin.is_open())
	{
		int oldScore;
		while (fin >> oldScore)
		{
			scores.push_back(oldScore);
		}
		fin.close();
	}

	// ���ο� ���� �߰�
	scores.push_back(score);

	// ������ ������������ ����
	std::sort(scores.begin(), scores.end(), [](int a, int b) { return a > b; });

	// ���� 10���� ������ ����
	if (scores.size() > 10)
	{
		scores.resize(10);
	}

	// ���Ͽ� ����
	std::ofstream fout("Rank.txt");
	if (fout.is_open())
	{
		for (int sortedScore : scores)
		{
			fout << sortedScore << "\n";
		}
		fout.close();
	}
}

void GameLevel::SpawnEnemyA()
{
	float enemySpeedA = RandomPercent(5.0f, 10.0f);
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
	float enemySpeedC = RandomPercent(3.0f, 5.0f);
	AddActor(new EnemyC("C", enemySpeedC));
}

void GameLevel::SpawnBomb()
{
	AddActor(new Bomb("@"));
}

void GameLevel::SpawnShield()
{
	AddActor(new Shield("S"));
}

void GameLevel::SpawnUpgrade()
{
	AddActor(new Upgrade("U"));
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
			// EnemyA ����
			enemyA->Destroy();

			// ���尡 �ִ� ����
			if (player->isShield)
			{
				player->DestroyShield();
				return;
			}

			// �÷��̾� ����
			player->Destroy();

			// �� 2�ʰ� ����
			Sleep(2000);

			// ���� ������ ���Ͽ� ����
			SaveScore(score);

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
			// EnemyB ����
			enemyB->Destroy();

			// ���尡 �ִ� ����
			if (player->isShield)
			{
				player->DestroyShield();
				return;
			}

			// �÷��̾� ����
			player->Destroy();

			// �� 2�ʰ� ����
			Sleep(2000);

			// ���� ������ ���Ͽ� ����
			SaveScore(score);

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
			// EnemyC ����
			enemyC->Destroy();

			// ���尡 �ִ� ����
			if (player->isShield)
			{
				player->DestroyShield();
				return;
			}

			// �÷��̾� ����
			player->Destroy();

			// �� 2�ʰ� ����
			Sleep(2000);

			// ���� ������ ���Ͽ� ����
			SaveScore(score);

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
		// ź��� �÷��̾ �浹�ߴ��� Ȯ��
		if (player->Intersect(*bullet))
		{
			// EnemyBullet ����
			bullet->Destroy();

			// ���尡 �ִ� ����
			if (player->isShield)
			{
				player->DestroyShield();
				return;
			}

			// �÷��̾� ����
			player->Destroy();

			// �� 2�ʰ� ����
			Sleep(2000);

			// ���� ������ ���Ͽ� ����
			SaveScore(score);

			// ���� ����
			Engine::Get().QuitGame();
		}
	}
}

void GameLevel::ProcessCollisionEnemyAndBullet()
{
	// ���� �÷��̾� ź�� ���� ����
	List<EnemyA*> enemyAs;
	List<EnemyB*> enemyBs;
	List<EnemyC*> enemyCs;
	List<PlayerBullet*> bullets;

	// ������ ��ġ�� ���͸� ��ȸ�ϸ鼭 ����Ʈ ä���
	for (Actor* actor : actors)
	{
		// EnemyA �˻�
		EnemyA* enemyA = actor->As<EnemyA>();
		if (enemyA)
		{
			enemyAs.PushBack(enemyA);
			continue;
		}

		// EnemyB �˻�
		EnemyB* enemyB = actor->As<EnemyB>();
		if (enemyB)
		{
			enemyBs.PushBack(enemyB);
			continue;
		}

		// EnemyC �˻�
		EnemyC* enemyC = actor->As<EnemyC>();
		if (enemyC)
		{
			enemyCs.PushBack(enemyC);
			continue;
		}

		// ź������ �� ��ȯ �� Ȯ���ؼ� ����Ʈ ä���
		PlayerBullet* bullet = actor->As<PlayerBullet>();
		if (bullet)
		{
			bullets.PushBack(bullet);
			continue;
		}
	}

	// ���� ó��
	if ((enemyAs.Size() == 0 && enemyBs.Size() == 0 && enemyCs.Size() == 0) || bullets.Size() == 0)
	{
		return;
	}

	// �迭�� ��ȸ�ϸ鼭 �浹 ó��
	for (PlayerBullet* bullet : bullets)
	{
 		for (EnemyA* enemyA : enemyAs)
		{
			if (enemyA->Intersect(*bullet))
			{
				// ���� ������Ʈ
				score += 10;

				// PlayerBullet ����
				bullet->Destroy();

				// enemyA ����
				enemyA->Destroy();
			}
		}

		for (EnemyB* enemyB : enemyBs)
		{
			if (enemyB->Intersect(*bullet))
			{
				// ���� ������Ʈ
				score += 20;

				// PlayerBullet ����
				bullet->Destroy();

				// enemyB ����
				enemyB->Destroy();
			}
		}

		for (EnemyC* enemyC : enemyCs)
		{
			if (enemyC->Intersect(*bullet))
			{
				// ���� ������Ʈ
				score += 30;

				// PlayerBullet ����
				bullet->Destroy();

				// enemyC ����
				enemyC->Destroy();
			}
		}
	}
}

void GameLevel::ProcessCollisionPlayerAndBomb()
{
	Player* player = nullptr;
	List<Bomb*> bombs;

	// ������ �ִ� ��� ���͸� ��ȸ
	for (Actor* actor : actors)
	{
		// �÷��̾� �˻�
		if (!player)
		{
			player = actor->As<Player>();
			continue;
		}

		// ��ź ������ �˻�
		Bomb* bomb = actor->As<Bomb>();
		if (bomb)
		{
			bombs.PushBack(bomb);
		}
	}

	// ���� ó��
	if (player == nullptr || bombs.Size() == 0)
	{
		return;
	}

	// ��ź �����۰� �÷��̾��� �浹 Ȯ��
	for (Bomb* bomb : bombs)
	{
		if (player->Intersect(*bomb))
		{
			// ��ź ������ ����
			bomb->Destroy();

			// �ʿ� �ִ� EnemyC �� ź�� ����
			for (Actor* actor : actors)
			{
				if (actor->As<EnemyC>())
				{
					actor->Destroy();
				}
			}
		}
	}
}

void GameLevel::ProcessCollisionPlayerAndShield()
{
	Player* player = nullptr;
	List<Shield*> shields;

	// ������ �ִ� ��� ���͸� ��ȸ
	for (Actor* actor : actors)
	{
		// �÷��̾� �˻�
		if (!player)
		{
			player = actor->As<Player>();
			continue;
		}

		// ���� ������ �˻�
		Shield* shield = actor->As<Shield>();
		if (shield)
		{
			shields.PushBack(shield);
		}
	}

	// ���� ó��
	if (player == nullptr || shields.Size() == 0)
	{
		return;
	}

	// ���� �����۰� �÷��̾��� �浹 Ȯ��
	for (Shield* shield : shields)
	{
		if (player->Intersect(*shield))
		{
			// ���� ������ ����
			shield->Destroy();

			// ���� ����
			player->CreateShield();
		}
	}
}

void GameLevel::ProcessCollisionPlayerAndUpgrade()
{
	Player* player = nullptr;
	Upgrade* upgrade = nullptr;

	// ������ �ִ� ��� ���͸� ��ȸ
	for (Actor* actor : actors)
	{
		// �÷��̾� �˻�
		if (!player)
		{
			player = actor->As<Player>();
			continue;
		}

		// ���׷��̵� ������ �˻�
		if (!upgrade)
		{
			upgrade = actor->As<Upgrade>();
			continue;
		}
	}

	// ���� ó��
	if (player == nullptr || upgrade == nullptr)
	{
		return;
	}

	if (player->Intersect(*upgrade))
	{
		// ���׷��̵� ������ ����
		upgrade->Destroy();

		// �Ѿ� �߻� ���� ����
		player->DecreseCooldown();
	}
}
