#pragma once
#include "Vector2.h"
#include "enum.h"
#include <vector>
#include <cassert>

class Bomb
{
private:
	Vector2Int pos;
	Direction direction;
	bool isExplosion = 0;
	int count;
	const int COUNT_MAX = 28;
public:
	Bomb() { pos = {}; direction = Up; count = COUNT_MAX; }
	Bomb(Vector2Int pos_, int dir);
	Vector2Int GetPos() { return pos; }
	Direction GetDirection() { return direction; }
	bool IsExplosion() { return isExplosion; }
	void Rotate();
	std::vector<Vector2Int> Explosion();
};

