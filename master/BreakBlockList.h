#pragma once
#include "Vector2.h"
#include <vector>

class BreakBlockList
{
private:
	static const int MiningTime = 10;
	static const int ExprosionTime = 5;
	std::vector<Vector2Int> blocks[2]{};
	Vector2Int front[2]{};
	int timer[2] = { 0, 0 };
	bool wait[2] = { false, false };
	int bombBreak = 0;
public:
	void Initialize();
	void Reset();
	void Update();
	void PushBuck(const Vector2Int& num, const bool bomb = false);
	bool PopBroken(Vector2Int& reciever);
	bool PopExposure(Vector2Int& reciever);
	void Clear();
	int GetBombBreak() { return bombBreak; }
	void DrawDebug();
};

