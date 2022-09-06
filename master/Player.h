#pragma once
#include "Vector2.h"
#include "Input.h"
class Player
{
private:
	Vector2 pos;
	int rad;
	float angle = 0;
	Input input;
	const float	MOVE_SPD = 5.0f, ROT_SPD = 0.1f;
public:
	Player(Vector2 pos_, int rad_);
	Vector2 GetPos() { return pos; }
	void Move(Vector2Int moveLimitLeftUp, Vector2Int moveRightDown);
	void Draw();
};