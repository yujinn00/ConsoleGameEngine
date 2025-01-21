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

#include <string>

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
	
	// 게임 타이머 업데이트
	ElapsedTime += deltaTime;

	// EnemyA 소환 타이머 업데이트
	spawnElapsedTimeA += deltaTime;
	if (spawnElapsedTimeA >= spawnIntervalA)
	{
		spawnElapsedTimeA = 0.0f;
		spawnIntervalA = RandomPercent(0.1f, 0.3f); // 새로운 랜덤 소환 간격 설정
		
		if (ElapsedTime < 15.0f)
		{
			SpawnEnemyA(); // EnemyA 소환
		}
	}

	// EnemyB 소환 타이머 업데이트
	spawnElapsedTimeB += deltaTime;
	if (spawnElapsedTimeB >= spawnIntervalB)
	{
		spawnElapsedTimeB = 0.0f;
		spawnIntervalB = RandomPercent(0.5f, 1.0f); // 새로운 랜덤 소환 간격 설정

		if (ElapsedTime > 20.0f && ElapsedTime < 35.0f)
		{
			SpawnEnemyB(); // EnemyB 소환
		}
	}

	// EnemyC 소환 타이머 업데이트
	spawnElapsedTimeC += deltaTime;
	if (spawnElapsedTimeC >= spawnIntervalC)
	{
		spawnElapsedTimeC = 0.0f;
		spawnIntervalC = RandomPercent(0.3f, 0.5f); // 새로운 랜덤 소환 간격 설정

		if (ElapsedTime > 40.0f && ElapsedTime < 55.0f)
		{
			SpawnEnemyC(); // EnemyC 소환
		}
	}

	// Bomb 소환 타이머 업데이트
	spawnElapsedTimeBomb += deltaTime;
	if (spawnElapsedTimeBomb >= spawnIntervalBomb)
	{
		spawnElapsedTimeBomb = 0.0f;
		spawnIntervalBomb = RandomPercent(5.0f, 10.0f); // 새로운 랜덤 소환 간격 설정
		SpawnBomb(); // Bomb 소환
	}

	// Shield 소환 타이머 업데이트
	spawnElapsedTimeShield += deltaTime;
	if (spawnElapsedTimeShield >= spawnIntervalShield)
	{
		spawnElapsedTimeShield = 0.0f;
		spawnIntervalShield = RandomPercent(5.0f, 10.0f); // 새로운 랜덤 소환 간격 설정
		SpawnShield(); // Shield 소환
	}

	// Upgrade 소환 타이머 업데이트
	spawnElapsedTimeUpgrade += deltaTime;
	if (spawnElapsedTimeUpgrade >= spawnIntervalUpgrade)
	{
		spawnElapsedTimeUpgrade = 0.0f;
		spawnIntervalUpgrade = 20.0f; // 소환 간격 20초 고정
		SpawnUpgrade(); // Upgrade 소환
	}

	// 충돌 처리 함수 호출
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
	// 테두리 그리기
	DrawBorder();

	// 액터 그리기
	for (Actor* actor : actors)
	{
		actor->Draw();
	}

	// 점수 출력하기
	std::string scoreText = "Score: " + std::to_string(score);
	Engine::Get().Draw(Vector2(Engine::Get().ScreenSize().x / 2 - 5, 0), scoreText.c_str(), Color::Green);
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
			// EnemyA 제거
			enemyA->Destroy();

			// 쉴드가 있는 상태
			if (player->isShield)
			{
				player->DestroyShield();
				return;
			}

			// 플레이어 제거
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
			// EnemyB 제거
			enemyB->Destroy();

			// 쉴드가 있는 상태
			if (player->isShield)
			{
				player->DestroyShield();
				return;
			}

			// 플레이어 제거
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
			// EnemyC 제거
			enemyC->Destroy();

			// 쉴드가 있는 상태
			if (player->isShield)
			{
				player->DestroyShield();
				return;
			}

			// 플레이어 제거
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
		// 탄약과 플레이어가 충돌했는지 확인
		if (player->Intersect(*bullet))
		{
			// EnemyBullet 제거
			bullet->Destroy();

			// 쉴드가 있는 상태
			if (player->isShield)
			{
				player->DestroyShield();
				return;
			}

			// 플레이어 제거
			player->Destroy();

			// 약 2초간 정지
			Sleep(2000);

			// 게임 종료
			Engine::Get().QuitGame();
		}
	}
}

void GameLevel::ProcessCollisionEnemyAndBullet()
{
	// 적과 플레이어 탄약 변수 선언
	List<EnemyA*> enemyAs;
	List<EnemyB*> enemyBs;
	List<EnemyC*> enemyCs;
	List<PlayerBullet*> bullets;

	// 레벨에 배치된 액터를 순회하면서 리스트 채우기
	for (Actor* actor : actors)
	{
		// EnemyA 검색
		EnemyA* enemyA = actor->As<EnemyA>();
		if (enemyA)
		{
			enemyAs.PushBack(enemyA);
			continue;
		}

		// EnemyB 검색
		EnemyB* enemyB = actor->As<EnemyB>();
		if (enemyB)
		{
			enemyBs.PushBack(enemyB);
			continue;
		}

		// EnemyC 검색
		EnemyC* enemyC = actor->As<EnemyC>();
		if (enemyC)
		{
			enemyCs.PushBack(enemyC);
			continue;
		}

		// 탄약으로 형 변환 후 확인해서 리스트 채우기
		PlayerBullet* bullet = actor->As<PlayerBullet>();
		if (bullet)
		{
			bullets.PushBack(bullet);
			continue;
		}
	}

	// 예외 처리
	if ((enemyAs.Size() == 0 && enemyBs.Size() == 0 && enemyCs.Size() == 0) || bullets.Size() == 0)
	{
		return;
	}

	// 배열을 순회하면서 충돌 처리
	for (PlayerBullet* bullet : bullets)
	{
 		for (EnemyA* enemyA : enemyAs)
		{
			if (enemyA->Intersect(*bullet))
			{
				// PlayerBullet 제거
				bullet->Destroy();

				// enemyA 제거
				enemyA->Destroy();
			}
		}

		for (EnemyB* enemyB : enemyBs)
		{
			if (enemyB->Intersect(*bullet))
			{
				// PlayerBullet 제거
				bullet->Destroy();

				// enemyB 제거
				enemyB->Destroy();
			}
		}

		for (EnemyC* enemyC : enemyCs)
		{
			if (enemyC->Intersect(*bullet))
			{
				// PlayerBullet 제거
				bullet->Destroy();

				// enemyC 제거
				enemyC->Destroy();
			}
		}
	}
}

void GameLevel::ProcessCollisionPlayerAndBomb()
{
	Player* player = nullptr;
	List<Bomb*> bombs;

	// 레벨에 있는 모든 액터를 순회
	for (Actor* actor : actors)
	{
		// 플레이어 검색
		if (!player)
		{
			player = actor->As<Player>();
			continue;
		}

		// 폭탄 아이템 검색
		Bomb* bomb = actor->As<Bomb>();
		if (bomb)
		{
			bombs.PushBack(bomb);
		}
	}

	// 예외 처리
	if (player == nullptr || bombs.Size() == 0)
	{
		return;
	}

	// 폭탄 아이템과 플레이어의 충돌 확인
	for (Bomb* bomb : bombs)
	{
		if (player->Intersect(*bomb))
		{
			// 폭탄 아이템 삭제
			bomb->Destroy();

			// 맵에 있는 모든 몬스터 및 탄약 삭제
			for (Actor* actor : actors)
			{
				if (actor->As<EnemyB>() || actor->As<EnemyC>() || actor->As<EnemyBullet>())
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
	Shield* shield = nullptr;

	// 레벨에 있는 모든 액터를 순회
	for (Actor* actor : actors)
	{
		// 플레이어 검색
		if (!player)
		{
			player = actor->As<Player>();
			continue;
		}

		// 쉴드 아이템 검색
		if (!shield)
		{
			shield = actor->As<Shield>();
			continue;
		}
	}

	// 예외 처리
	if (player == nullptr || shield == nullptr)
	{
		return;
	}

	if (player->Intersect(*shield))
	{
		// 쉴드 아이템 삭제
		shield->Destroy();

		// 쉴드 생성
		player->CreateShield();

	}
}

void GameLevel::ProcessCollisionPlayerAndUpgrade()
{
	Player* player = nullptr;
	Upgrade* upgrade = nullptr;

	// 레벨에 있는 모든 액터를 순회
	for (Actor* actor : actors)
	{
		// 플레이어 검색
		if (!player)
		{
			player = actor->As<Player>();
			continue;
		}

		// 업그레이드 아이템 검색
		if (!upgrade)
		{
			upgrade = actor->As<Upgrade>();
			continue;
		}
	}

	// 예외 처리
	if (player == nullptr || upgrade == nullptr)
	{
		return;
	}

	if (player->Intersect(*upgrade))
	{
		// 업그레이드 아이템 삭제
		upgrade->Destroy();

		// @Todo: 업그레이드 아이템 먹으면 총알 발사 쿨타임 줄어들게 .. (0회 먹으면 발사 못함, 1회 먹으면 쿨 2초, 2회 먹으면 쿨 1초, 3회 먹으면 쿨 0.1초
	}
}
