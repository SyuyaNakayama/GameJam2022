#pragma once
class Vector2Int
{
public:
	int x = 0, y = 0;

	Vector2Int() {}
	Vector2Int(int x, int y) { this->x = x, this->y = y; }
};

class Vector2
{
public:
	float x, y;

public:
	Vector2();
	Vector2(float x, float y);

	float length() const; // �m����(����)
	Vector2& normalize(); // ���K��
	float dot(const Vector2& v) const; // ���ϒl
	float cross(const Vector2& v) const; // �O�ϒl

	// �P�����Z�q�I�[�o�[���[�h
	Vector2 operator+() const;
	Vector2 operator-() const;

	// ������Z�q�I�[�o�[���[�h
	Vector2& operator+=(const Vector2& v);
	Vector2& operator-=(const Vector2& v);
	Vector2& operator*=(float s);
	Vector2& operator/=(float s);
};

// 2�����Z�q�I�[�o�[���[�h
const Vector2 operator+(const Vector2& v1, const Vector2& v2);
const Vector2 operator-(const Vector2& v1, const Vector2& v2);
const Vector2 operator*(const Vector2& v, float s);
const Vector2 operator*(float s, const Vector2& v);
const Vector2 operator/(const Vector2& v, float s);