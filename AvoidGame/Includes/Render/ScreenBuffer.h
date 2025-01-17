#pragma once

#include "Core.h"
#include "Math/Vector2.h"

// ȭ�� ���ۿ� ����� ����
struct Character
{
	// ����
	char image;

	// ���� ����
	Color color;
};

// ���� ���۸� ������ ����� ȭ�� ���� Ŭ����
class ScreenBuffer
{
	friend class Engine;

public:
	// �����ڿ� ũ�⸸ �����ϸ�, ���ο� �ܼ� ���۸� ����
	ScreenBuffer(const COORD& size);

	// �����ڿ� HANDLE�� �����ϸ�, ǥ�� ��� �ڵ��� ����� �ܼ� ���� ����
	ScreenBuffer(HANDLE console, const COORD& size);

	// �Ҹ���
	~ScreenBuffer();

	// Ŀ�� Ÿ�� ����(Ŀ�� ���߱� ����) �Լ�
	void SetCursorType(CursorType cursorType);

	// ���� ����� �Լ�
	void Clear();

	// �ܼ� ���ۿ� ��ü ���ڿ� ���۸� �� �� ����ϴ� �Լ�
	void Draw(CHAR_INFO* buffer);

private:
	// �ܼ� �ڵ�
	HANDLE buffer;

	// �ܼ� ȭ�� ũ��
	COORD size;
};
