#pragma once
class Vector2Int
{
public:
	int x = 0, y = 0;

	Vector2Int() {}
	Vector2Int(int x, int y) { this->x = x, this->y = y; }

	Vector2Int absVec();
	// ������Z�q�I�[�o�[���[�h
	Vector2Int& operator+=(const Vector2Int& v);
	Vector2Int& operator-=(const Vector2Int& v);
	Vector2Int& operator*=(float s);
	Vector2Int& operator/=(float s);

	bool operator==(Vector2Int v);
};

// 2�����Z�q�I�[�o�[���[�h
const Vector2Int operator+(const Vector2Int& v1, const Vector2Int& v2);
const Vector2Int operator-(const Vector2Int& v1, const Vector2Int& v2);
const Vector2Int operator*(const Vector2Int& v, float s);
const Vector2Int operator*(float s, const Vector2Int& v);
const Vector2Int operator/(const Vector2Int& v, float s);

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