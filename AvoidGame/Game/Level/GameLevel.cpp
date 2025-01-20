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

	// EnemyA 시작 후 1초부터 생성
	spawnIntervalA = 1.0f;

	// EnemyB 시작 후 5초부터 생성
	spawnIntervalB = 5.0f;

	// EnemyC 시작 후 10초부터 생성
	spawnIntervalC = 10.0f;
}

void GameLevel::Update(float deltaTime)
{
	Super::Update(deltaTime);

	if (Engine::Get().GetKeyDown(VK_ESCAPE))
	{
		Game::Get().ToggleLevel("Game Menu");
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
		spawnIntervalB = RandomPercent(0.5f, 2.0f); // 새로운 랜덤 소환 간격 설정
		SpawnEnemyB(); // EnemyB 소환
	}

	// EnemyC 소환 타이머 업데이트
	spawnElapsedTimeC += deltaTime;
	if (spawnElapsedTimeC >= spawnIntervalC)
	{
		spawnElapsedTimeC = 0.0f;
		spawnIntervalC = RandomPercent(1.0f, 3.0f); // 새로운 랜덤 소환 간격 설정
		SpawnEnemyC(); // EnemyC 소환
	}

	ProcessCollisionPlayerAndEnemyA();
	ProcessCollisionPlayerAndEnemyB();
	ProcessCollisionPlayerAndBullet();
	ProcessCollisionPlayerAndEnemyC();
}

void GameLevel::Draw()
{
	// 테두리 그리기
	DrawBorder();

	// 액터 그리기
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
	// 화면 크기 가져오기
	Vector2 screenSize = Engine::Get().ScreenSize();

	// 위쪽과 아래쪽 테두리
	for (int x = 0; x < screenSize.x; ++x)
	{
		// 위쪽 테두리
		Engine::Get().Draw(Vector2(x, 0), "-", Color::White);

		// 아래쪽 테두리
		Engine::Get().Draw(Vector2(x, screenSize.y - 1), "-", Color::White);
	}

	// 왼쪽과 오른쪽 테두리
	for (int y = 0; y < screenSize.y; ++y)
	{
		// 왼쪽 테두리
		Engine::Get().Draw(Vector2(0, y), "|", Color::White);

		// 오른쪽 테두리
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

		// EnemyA로 형 변환 후 확인해서 리스트 채우기
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
		// Player와 EnemyA가 충돌했는지 확인
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
	// Player와 EnemyB 배열 선언
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

		// EnemyB로 형 변환 후 확인해서 리스트 채우기
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
		// Player와 EnemyB가 충돌했는지 확인
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

void GameLevel::ProcessCollisionPlayerAndEnemyC()
{
	// Player와 EnemyC 배열 선언
	Player* player = nullptr;
	List<EnemyC*> enemyCs;

	// 레벨에 배치된 액터를 순회하면서 리스트 채우기
	for (Actor* actor : actors)
	{
		// 플레이어 검색
		if (!player)
		{
			player = actor->As<Player>();
			continue;
		}

		// EnemyC로 형 변환 후 확인해서 리스트 채우기
		EnemyC* enemyC = actor->As<EnemyC>();
		if (enemyC)
		{
			enemyCs.PushBack(enemyC);
			continue;
		}
	}

	// 예외 처리
	if (player == nullptr || enemyCs.Size() == 0)
	{
		return;
	}

	// 배열을 순회하면서 충돌 처리
	for (EnemyC* enemyC : enemyCs)
	{
		// Player와 EnemyC가 충돌했는지 확인
		if (player->Intersect(*enemyC))
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
