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
	bool isExplsion = 0;
public:
	Bomb() { pos = {}; direction = Up; }
	Bomb(Vector2Int pos_, int dir);
	Vector2Int GetPos() { return pos; }
	void Rotate();
	std::vector<Vector2Int> Explosion();
};

