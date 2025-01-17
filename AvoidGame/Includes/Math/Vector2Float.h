#pragma once

#include "Core.h"

class ENGINE_API Vector2Float
{
public:
	Vector2Float(float x = 0.0f, float y = 0.0f);
	~Vector2Float() = default;

	// 연산자 오버로딩
	Vector2Float operator+(const Vector2Float& other);
	Vector2Float operator-(const Vector2Float& other);
	Vector2Float operator+=(const Vector2Float& other);
	Vector2Float operator-=(const Vector2Float& other);

public:
	// x 좌표 및 y 좌표
	float x = 0.0f;
	float y = 0.0f;
};
