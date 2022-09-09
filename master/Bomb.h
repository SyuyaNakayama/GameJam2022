#pragma once
#include "Vector2.h"
#include "enum.h"
#include <vector>

class Bomb
{
private:
	Vector2Int pos;
	Direction direction;

public:
	Bomb() { pos = {}; direction = Up; }
	Bomb(Vector2Int pos_, int dir);
	Vector2Int GetPos() { return pos; }
	void Rotate();
	std::vector<Vector2Int> Explosion();
};

