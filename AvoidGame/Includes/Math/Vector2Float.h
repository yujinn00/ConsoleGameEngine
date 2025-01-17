#pragma once

#include "Core.h"

class ENGINE_API Vector2Float
{
public:
	Vector2Float(float x = 0.0f, float y = 0.0f);
	~Vector2Float() = default;

	// ������ �����ε�
	Vector2Float operator+(const Vector2Float& other);
	Vector2Float operator-(const Vector2Float& other);
	Vector2Float operator+=(const Vector2Float& other);
	Vector2Float operator-=(const Vector2Float& other);

public:
	// x ��ǥ �� y ��ǥ
	float x = 0.0f;
	float y = 0.0f;
};
