#include "TextScrollActor.h"
#include "Engine/Engine.h"

TextScrollActor::TextScrollActor(const char* message)
{
	// ���ڿ� ���� ���ϱ�
	length = (int)strlen(message);

	// ���ڿ� ����
	string = new char[length + 1];
	strcpy_s(string, length + 1, message);

	// Ŀ�� ���߱�
	Engine::Get().SetCursorType(CursorType::NoCursor);
}

TextScrollActor::~TextScrollActor()
{
	delete[] string;
}

void TextScrollActor::Update(float deltaTime)
{
	// ESC ����
	if (Engine::Get().GetKeyDown(VK_ESCAPE))
	{
		Engine::Get().QuitGame();
	}

	// ������ ���
	elapsedTime += deltaTime;

	// �ð��� ��� ����ߴ��� Ȯ��
	if (elapsedTime < delayTime)
	{
		return;
	}

	// �ð��� ��������� ���� ����� ���� �ʱ�ȭ
	elapsedTime = 0.0f;

	// ȭ�鿡 �׸� ���ڿ��� ���� �ε��� ������Ʈ
	index = (index + 1) % length;
}

void TextScrollActor::Draw()
{
	// �ӽ� ���ڿ� ����
	char* temp = new char[printWidth + 1];
	int tempIndex = index;

	for (int i = 0; i < printWidth; ++i)
	{
		temp[i] = string[tempIndex];
		tempIndex = (tempIndex + 1) % length;
	}

	temp[printWidth] = '\0';
	Log(temp);

	delete[] temp;
	Engine::Get().SetCursorPosition(0, 0);
}
