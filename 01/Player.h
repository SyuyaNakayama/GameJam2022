#pragma once
#include "Vector2.h"
#include "Input.h"
#include "Map.h"
#include "Pad.h"
#include <vector>
#include <array>

enum Direction { Up, Down, Left, Right };
enum Mode { Move, Select };

class Map;

class Player
{
private:
	static const int DESTROY_MAX = 3;

	Vector2Int pos, selectPos;
	int rad;
	Direction direction = Up;
	Input input;
	Pad pad;
	int selectNum = DESTROY_MAX;
	int actionNum = 20;
	int respawnTimer = 0;
	int respawnTimerLimit = 120;
	std::vector<Vector2Int> selectChip;
	Mode mode = Mode::Move;
	Map* mapPointer;
	bool destroyAnimetionFlag = 0;
	bool countStartFlag = 0;
public:
	Player(Vector2Int pos_, Map* pMap);
	void SetPos(Vector2Int pos_) { pos = pos_; }
	Vector2Int GetPos() { return pos; }
	Direction GetDirection() { return direction; }
	void Move();
	void Draw();
	void Destroy();
	int GetActionCount() { return actionNum; }
};