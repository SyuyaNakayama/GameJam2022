#pragma once
#include "Selecter.h"
#include "Input.h"
#include <vector>

class Map;

class Player
{
private:
	static const int DESTROY_MAX = 3;

	Vector2Int pos;
	int direction = 0;
	int actionNum = 15;
	int damageCount = 0;
	Selecter selecter;
	Vector2Int move;

	int mode = 0;
	int next = 0;
	int stopTimer = 0;

	Map* pMap = nullptr;
	Input* input;
public:
	void LoadAndSet(Map* pMap);
	void Initialize(const Vector2Int& pos, const int direction);
	void Reset(const Vector2Int& pos, const int direction);
	void Update();
	void Draw(const Vector2Int& camera);
private:
	void ActionReset();
	void Action();
	void Stop();
	void Select();
	void Destroy();
	void Move();
public:
	Vector2Int GetPos() { return pos; }
	Vector2Int* GetPosAdress() { return &pos; }
	int GetDirection() { return direction; }
	void SetPos(const Vector2Int& pos) { this->pos = pos; }
	int GetActionCount() { return actionNum; }
	int* GetActionCountPointer() { return &actionNum; }
	int GetDamageCount() { return damageCount; }
	void DamageCountUp() { damageCount++; }
};