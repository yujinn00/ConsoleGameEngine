#pragma once

#include "Core.h"

// �ʽð� Ŭ����
class ENGINE_API Timer
{
public:
	// �����ڿ��� Ÿ�̸��� ��ǥ �ð� ����
	Timer(float targetTime);

	// Ÿ�̸� ������Ʈ
	void Update(float deltaTime);

	// Ÿ�̸� �ʱ�ȭ
	void Reset();

	// Ÿ�̸Ӱ� ��ǥ �ð��� ����ߴ��� Ȯ��
	inline bool IsTimeOut() const { return elapsedTime >= targetTime; }

	// ��ǥ �ð��� ������ �� ����� ����
	inline void SetTime(float targetTime) { this->targetTime = targetTime; }

private:
	// ��� �ð�
	float elapsedTime = 0.0f;

	// ��ǥ �ð�
	float targetTime = 0.0f;
};
