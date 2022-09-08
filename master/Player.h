#pragma once
#include "Vector2.h"
#include "Input.h"
#include "Map.h"
#include "Pad.h"
#include <vector>

enum Direction { Up, Down, Left, Right };
enum Mode{Move,Select};

class Map;

class Player
{
private:
	static const int DESTROY_MAX = 3;

	Vector2Int pos,selectPos;
	int rad;
	Direction direction = Up;
	Input input;
	Pad pad;
	int selectNum = DESTROY_MAX;
	std::vector<Vector2Int> selectChip;
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