#include "GameLevel.h"
#include "Engine/Engine.h"
#include "Actor/Player.h"
#include "Actor/EnemyA.h"
#include "Actor/EnemyB.h"
#include "Actor/EnemyBullet.h"

GameLevel::GameLevel()
{
	AddActor(new Player("P"));

	// EnemyA 시작 후 1초부터 생성
	spawnIntervalA = 1.0f;

	// EnemyB 시작 후 10초부터 생성
	spawnIntervalB = 10.0f;
}

GameLevel::~GameLevel()
{
}

void GameLevel::Update(float deltaTime)
{
	Super::Update(deltaTime);

	// ESC 종료
	if (Engine::Get().GetKeyDown(VK_ESCAPE))
	{
		Engine::Get().QuitGame();
	}

	// EnemyA 소환 타이머 업데이트
	spawnElapsedTimeA += deltaTime;
	if (spawnElapsedTimeA >= spawnIntervalA)
	{
		spawnElapsedTimeA = 0.0f;
		spawnIntervalA = RandomPercent(0.1f, 1.0f); // 새로운 랜덤 소환 간격 설정
		SpawnEnemyA(); // EnemyA 소환
	}

	// EnemyB 소환 타이머 업데이트
	spawnElapsedTimeB += deltaTime;
	if (spawnElapsedTimeB >= spawnIntervalB)
	{
		spawnElapsedTimeB = 0.0f;
		spawnIntervalB = RandomPercent(1.0f, 3.0f); // 새로운 랜덤 소환 간격 설정
		SpawnEnemyB(); // EnemyB 소환
	}

	ProcessCollisionPlayerAndEnemyA();
	ProcessCollisionPlayerAndEnemyB();
	ProcessCollisionPlayerAndBullet();
}

void GameLevel::SpawnEnemyA()
{
	float enemySpeedA = RandomPercent(7.0f, 15.0f);
	AddActor(new EnemyA("A", enemySpeedA));
}

void GameLevel::SpawnEnemyB()
{
	float enemySpeedB = RandomPercent(3.0f, 5.0f);
	SpawnPosition spawnPosition = static_cast<SpawnPosition>(Random(0, 3));
	AddActor(new EnemyB("B", spawnPosition, enemySpeedB));
}

void GameLevel::ProcessCollisionPlayerAndEnemyA()
{
	// Player와 EnemyA 배열 선언
	Player* player = nullptr;
	List<EnemyA*> enemyAs;

	// 레벨에 배치된 액터를 순회하면서 리스트 채우기
	for (Actor* actor : actors)
	{
		// 플레이어 검색
		if (!player)
		{
			player = actor->As<Player>();
			continue;
		}

		// EnemyA으로 형 변환 후 확인해서 리스트 채우기
		EnemyA* enemyA = actor->As<EnemyA>();
		if (enemyA)
		{
			enemyAs.PushBack(enemyA);
			continue;
		}
	}

	// 예외 처리
	if (player == nullptr || enemyAs.Size() == 0)
	{
		return;
	}

	// 배열을 순회하면서 충돌 처리
	for (EnemyA* enemyA : enemyAs)
	{
		// 탄약과 플레이어가 충돌했는 확인
		if (player->Intersect(*enemyA))
		{
			// 플레이어 사망
			player->Destroy();

			// 약 2초간 정지
			Sleep(2000);

			// 게임 종료
			Engine::Get().QuitGame();
		}
	}
}

void GameLevel::ProcessCollisionPlayerAndEnemyB()
{
	// Player와 EnemyA 배열 선언
	Player* player = nullptr;
	List<EnemyB*> enemyBs;

	// 레벨에 배치된 액터를 순회하면서 리스트 채우기
	for (Actor* actor : actors)
	{
		// 플레이어 검색
		if (!player)
		{
			player = actor->As<Player>();
			continue;
		}

		// EnemyA으로 형 변환 후 확인해서 리스트 채우기
		EnemyB* enemyB = actor->As<EnemyB>();
		if (enemyB)
		{
			enemyBs.PushBack(enemyB);
			continue;
		}
	}

	// 예외 처리
	if (player == nullptr || enemyBs.Size() == 0)
	{
		return;
	}

	// 배열을 순회하면서 충돌 처리
	for (EnemyB* enemyB : enemyBs)
	{
		// 탄약과 플레이어가 충돌했는 확인
		if (player->Intersect(*enemyB))
		{
			// 플레이어 사망
			player->Destroy();

			// 약 2초간 정지
			Sleep(2000);

			// 게임 종료
			Engine::Get().QuitGame();
		}
	}
}

void GameLevel::ProcessCollisionPlayerAndBullet()
{
	// 플레이어와 적 탄약 변수 선언
	Player* player = nullptr;
	List<EnemyBullet*> bullets;

	// 레벨에 배치된 액터를 순회하면서 리스트 채우기
	for (Actor* actor : actors)
	{
		// 플레이어 검색
		if (!player)
		{
			player = actor->As<Player>();
			continue;
		}

		// 탄약으로 형 변환 후 확인해서 리스트 채우기
		EnemyBullet* bullet = actor->As<EnemyBullet>();
		if (bullet)
		{
			bullets.PushBack(bullet);
			continue;
		}
	}

	// 예외 처리
	if (player == nullptr || bullets.Size() == 0)
	{
		return;
	}

	// 배열을 순회하면서 충돌 처리
	for (EnemyBullet* bullet : bullets)
	{
		// 탄약과 플레이어가 충돌했는 확인
		if (player->Intersect(*bullet))
		{
			// 플레이어 사망
			player->Destroy();

			// 약 2초간 정지
			Sleep(2000);

			// 게임 종료
			Engine::Get().QuitGame();
		}
	}
}
