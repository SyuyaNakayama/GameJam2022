#pragma once
#include "Vector2.h"
#include <vector>

class BreakBlockList
{
private:
	static const int MiningTime = 10;
	static const int ExprosionTime = 5;
	struct BreakBlockPara 
	{
		Vector2Int number = { -1, -1 };
		bool exposure = false;
	};
	std::vector<BreakBlockPara> blocks;
	Vector2Int front;
	int timer = 0;
	bool wait = false;
	int waitTime = 0;
	int bombBreak = 0;
public:
	void Initialize();
	void Update();
	void PushBuck(const Vector2Int& num, const bool bomb = false);
	bool PopFront(Vector2Int& reciever);
	void Clear();
	int GetBombBreak() { return bombBreak; }
	void DrawDebug();
};

