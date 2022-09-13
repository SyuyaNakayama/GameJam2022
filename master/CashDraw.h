#pragma once
#include "Vector2.h"
#include "Ease.h"
#include <vector>

class CashDraw
{
private:
	struct CoinCount
	{
		int height = 0;
		int trans = 0;
		Ease ease;
	};
	int* pCoinCount = nullptr;
	int elderNum = 0;
	std::vector<CoinCount> coins;
	int count = 0;
	int timer = 0;
	int coinG = 0;
public:
	void Load();
	void SetCoinCount(int* coinCount);
	void Initialize();
	void Update();
	void Draw(const Vector2Int& pos, const Vector2Int& camera);
public:
	void Emit();
	void Move();
	void DrawCoins(const Vector2Int& pos, const Vector2Int& camera);
};

