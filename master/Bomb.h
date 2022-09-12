#pragma once
#include "Vector2.h"
#include <vector>

class Bomb
{
private:
	Vector2Int pos;
	int direction = 0;
	bool isExplosion = 0;
	int timer = 0;
	static const int RotaTimer = 28;
public:
	void Initialize(const Vector2Int& pos, const int direction);
	Vector2Int GetPos() { return pos; }
	int GetDirection() { return direction; }
	bool IsExplosion() { return isExplosion; }
	void Rotate();
	std::vector<Vector2Int> Explosion();
};

