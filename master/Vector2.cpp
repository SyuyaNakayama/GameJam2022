#include "Vector2.h"
#include <cmath>

Vector2Int Vector2Int::absVec()
{
	return { abs(x),abs(y)};
}

Vector2Int& Vector2Int::operator+=(const Vector2Int& v)
{
	x += v.x;
	y += v.y;
	return *this;
}
Vector2Int& Vector2Int::operator-=(const Vector2Int& v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}
Vector2Int& Vector2Int::operator*=(float s)
{
	x *= s;
	y *= s;
	return *this;
}
Vector2Int& Vector2Int::operator/=(float s)
{
	x /= s;
	y /= s;
	return *this;
}

bool Vector2Int::operator==(Vector2Int v)
{
	return x == v.x && y == v.y;
}

const Vector2Int operator+(const Vector2Int& v1, const Vector2Int& v2)
{
	Vector2Int temp(v1);
	return temp += v2;
}
const Vector2Int operator-(const Vector2Int& v1, const Vector2Int& v2)
{
	Vector2Int temp(v1);
	return temp -= v2;
}
const Vector2Int operator*(const Vector2Int& v, float s)
{
	Vector2Int temp(v);
	return temp *= s;
}
const Vector2Int operator*(float s, const Vector2Int& v) { return v * s; }
const Vector2Int operator/(const Vector2Int& v, float s)
{
	Vector2Int temp(v);
	return temp /= s;
}


Vector2::Vector2() { x = 0.0f, y = 0.0f; }
Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

float Vector2::length() const { return sqrtf(x * x + y * y); }
Vector2& Vector2::normalize()
{
	float len = length();
	if (len != 0)
	{
		return *this /= len;
	}
	return *this;
}
float Vector2::dot(const Vector2& v) const { return x * v.x + y * v.y; }
float Vector2::cross(const Vector2& v) const { return x * v.y - y * v.x; }

Vector2 Vector2::operator+() const { return *this; }
Vector2 Vector2::operator-() const { return Vector2(-x, -y); }

Vector2& Vector2::operator+=(const Vector2& v)
{
	x += v.x;
	y += v.y;
	return *this;
}
Vector2& Vector2::operator-=(const Vector2& v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}
Vector2& Vector2::operator*=(float s)
{
	x *= s;
	y *= s;
	return *this;
}
Vector2& Vector2::operator/=(float s)
{
	x /= s;
	y /= s;
	return *this;
}

const Vector2 operator+(const Vector2& v1, const Vector2& v2)
{
	Vector2 temp(v1);
	return temp += v2;
}
const Vector2 operator-(const Vector2& v1, const Vector2& v2)
{
	Vector2 temp(v1);
	return temp -= v2;
}
const Vector2 operator*(const Vector2& v, float s)
{
	Vector2 temp(v);
	return temp *= s;
}
const Vector2 operator*(float s, const Vector2& v) { return v * s; }
const Vector2 operator/(const Vector2& v, float s)
{
	Vector2 temp(v);
	return temp /= s;
}