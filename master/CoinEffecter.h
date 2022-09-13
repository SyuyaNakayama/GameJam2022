#pragma once
#include "Vector2.h"
#include "Ease.h"
#include <vector>

class CoinEffecter
{
private:
	struct CoinEffect
	{
		Vector2Int pos;
		int height = 0;
		int trans = 0;
		Ease ease;
		bool jet = false;
	};
	std::vector<CoinEffect> effects;
	int coinG = 0;
	Vector2Int* leftTop = nullptr;
public:
	void Load();
	void Emit(const Vector2Int& num);
	void Clear();
	void Update();
	void Draw(const Vector2Int& camera);
	void SetLeftTop(Vector2Int* leftTop);
private:
	void Erase(const int num);
};