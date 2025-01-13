#pragma once

// 레벨의 기본 물체
class ENGINE_API Actor
{
public:
	Actor();
	virtual ~Actor();

	// 루프 처리 함수
	virtual void Update(float deltaTime);
	virtual void Draw();

protected:
	// 활성화 상태인지 나타내는 변수
	bool isActive;

	// 액터의 제거 요청이 됐는지 나타내는 변수
	bool isExpired;
};
