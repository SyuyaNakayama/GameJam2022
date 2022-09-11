#pragma once
#include "SelectDraw.h"
#include <vector>

class Map;

class Select
{
private:
	Vector2Int pos;
	int direction = -1;
	std::vector<Vector2Int> chose;
	int choseMax = 0;

	SelectDraw drawer;

	Vector2Int* playerPos = nullptr;
	Map* pMap = nullptr;
public:
	void Load();
	void Initialize(const int choseMax);
	void Update();
	void Draw(const Vector2Int& camera);
	void SetPlayerPos(Vector2Int* playerPos);
	void SetMap(Map* map);
private:
	void DirectionUpdate();
	void ChipSelect();
	void Move();
};