#pragma once
#include "SelectDraw.h"
#include "Input.h"
#include <vector>

class Map;

class Selecter
{
private:
	Vector2Int pos;
	int direction = 0;

	std::vector<Vector2Int> chose;
	int choseMax = 0;
	bool decision = false;
	bool bomb = false;

	SelectDraw drawer;

	Vector2Int* playerPos = nullptr;
	Map* pMap = nullptr;
	Input* input = nullptr;
public:
	void Load();
	void Initialize(const int choseMax, const int direction);
	void Reset(const int direction);
	void Update();
	void Draw(const Vector2Int& camera);
	void SetPlayerPos(Vector2Int* playerPos);
	void SetMap(Map* map);
	Vector2Int GetRoutePos(const int num);
	Vector2Int GetRouteBack();
	int GetDirection() { return direction; }
	size_t GetRouteSize() { return chose.size(); }
	void EraseRoute(const int num);
	bool IsDecision() { return decision; }
	bool IsSelectBomb() { return bomb; }
private:
	void SummaryUpdate();
	void DirectionUpdate();
	void ChipSelect();
	void Move();
};