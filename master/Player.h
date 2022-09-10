#pragma once
#include "Vector2.h"
#include "Input.h"
#include "Map.h"
#include "Pad.h"
#include "enum.h"
#include <vector>

class Map;

class Player
{
private:
	static const int DESTROY_MAX = 3;

	Vector2Int pos, selectPos;
	int rad;
	Direction direction = Up;
	Input input;
	Pad* pad = nullptr;
	int selectNum = DESTROY_MAX;
	int actionNum = 20;
	int respawnTimer = 0;
	int respawnTimerLimit = 120;
	std::vector<Vector2Int> selectChip;
	Mode mode = Mode::Move;
	Map* mapPointer;
	bool destroyAnimetionFlag = 0;
	bool countStartFlag = 0;
	int damageCount = 0;
public:
	Player(Vector2Int pos_, Map* pMap);
	void SetPos(Vector2Int pos_) { pos = pos_; }
	Vector2Int GetPos() { return pos; }
	Vector2Int* GetPosAdress() { return &pos; }
	Direction GetDirection() { return direction; }
	int GetActionCount() { return actionNum - damageCount; }
	Vector2Int GetLastSelectChip() { return selectChip[selectChip.size() - 2]; }
	int GetDamageCount() { return damageCount; }
	void DamageCountUp() { damageCount++; }
	void Move();
	void Draw();
	void Destroy();
};