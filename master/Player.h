#pragma once
#include "Vector2.h"
#include "Input.h"
#include "Map.h"
#include "Pad.h"

enum Direction { Up, Down, Left, Right };
enum Mode{Move,Select};

class Map;

class Player
{
private:
	Vector2Int pos,selectPos;
	int rad;
	Direction direction = Up;
	Input input;
	Pad pad;
	const float	MOVE_SPD = 5.0f, ROT_SPD = 0.1f;
	int selectNum = 3;
	Mode mode = Mode::Move;
	Map* mapPointer;
public:
	Player(Vector2Int pos_, int rad_,Map* pMap);
	Vector2Int GetPos() { return pos; }
	Direction GetDirection() { return direction; }
	void Move();
	void Draw();
	void Destroy();
};