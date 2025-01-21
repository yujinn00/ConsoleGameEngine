#pragma once

#include "Core.h"
#include "Math/Vector2.h"

// �Է� ó���� ���� ����ü
struct KeyState
{
	// ���� �����ӿ� Ű�� ���ȴ��� Ȯ��
	bool isKeyDown = false;

	// ���� �����ӿ� Ű�� ���Ⱦ����� Ȯ��
	bool wasKeyDown = false;
};

// ���� Ŭ����
class Level;
class Actor;
class ScreenBuffer;
class ENGINE_API Engine
{
public:
	Engine();
	virtual ~Engine();

	// ���� ���� �Լ�
	void Run();

	// ���� �߰� �Լ�
	void LoadLevel(Level* newLevel);

	// ���� ���� ��ȯ �Լ�
	Level* GetCurrentLevel() const;

	// ���� �߰� �� ���� �Լ�
	void AddActor(Actor* newActor);
	void DestroyActor(Actor* targetActor);

	// ȭ�� ��ǥ ���� �Լ�
	void SetCursorType(CursorType cursorType);

	void Draw(const Vector2& position, const char* image, Color color = Color::White);

	// ȭ�� ũ�� ��ȯ �Լ�
	inline Vector2 ScreenSize() const { return screenSize; };

	// Ÿ�� ������ �ӵ� ���� �Լ�
	void SetTargetFrameRate(float targetFrameRate);

	// �Է� ���� �Լ�
	bool GetKey(int key);
	bool GetKeyDown(int key);
	bool GetKeyUp(int key);

	// ���� ���� �Լ�
	void QuitGame();

	// �̱��� ��ü ���� �Լ�
	static Engine& Get();

protected:
	void ProcessInput();			// �Է� ó��
	void Update(float deltaTime);	// Tick();

	void Clear();					// ȭ�� �����
	void Draw();					// Render();
	void Present();

	// ���� Ű ���¸� �����ϴ� �Լ�
	void SavePreviousKeyStates();

	inline ScreenBuffer* GetRenderer() const { return renderTargets[currentRenderTargetIndex]; }
	void ClearImageBuffer();

protected:
	// Ÿ�� ������ ���� (�ʴ� ������)
	float targetFrameRate = 60.0f;

	// �� ������ �ð� �� (����: ��)
	float targetOneFrameTime = 0.0f;

	// ������ �� ������ ����
	bool quit;

	// Ű ���¸� �����ϴ� �迭
	KeyState keyState[255];

	// �̱��� ������ ���� ���� ���� ����
	static Engine* instance;

	// ���� ���� ����
	Level* mainLevel;

	// �������� ������Ʈ�ؾ� �ϴ��� ���θ� ��Ÿ���� ����
	bool shouldUpdate = true;

	// ȭ�� ũ��
	Vector2 screenSize;

	// ȭ�� ���� �� ����� ���� (Blob)
	CHAR_INFO* imageBuffer = nullptr;

	// ȭ�� ����.
	ScreenBuffer* renderTargets[2];
	int currentRenderTargetIndex = 0;
};
