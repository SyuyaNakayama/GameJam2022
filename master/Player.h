#pragma once
#include "Vector2.h"
#include "Input.h"
#include "Map.h"
#include "Pad.h"

enum Direction { Up, Down, Left, Right };

class Map;

class Player
{
private:
	Vector2Int pos;
	int rad;
	Direction direction = Up;
	Input input;
	Pad pad;
	const float	MOVE_SPD = 5.0f, ROT_SPD = 0.1f;
public:
	Player(Vector2Int pos_, int rad_);
	Vector2Int GetPos() { return pos; }
	Direction GetDirection() { return direction; }
	void Move(Map& map);
	void Draw(Map& map);
};