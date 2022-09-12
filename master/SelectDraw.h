#pragma once
#include "Vector2.h"
#include "Ease.h"
#include <vector>

class SelectDraw
{
private:
	struct ChoseState
	{
		Vector2Int pos;
		float rota = 0.0f;
		float scale = 0.0f;
		int trans = 0;
		Ease2 ease;
		bool isChose = false;
		int number = 0;
	};
private:
	Vector2Int leftTop;
	Vector2Int dist;
	Ease2 ease;
	bool isEase = false;
	std::vector<ChoseState> locks;
	int setG = 0;
	int lockG = 0;
public:
	void Load();
	void Initialize(const Vector2Int& leftTop);
	void Reset();
	void Update();
	void CreateChose(const Vector2Int& num, const int number);
	void EraseChose(const int number);
	void ClearChose();
	void ChoseDraw(const Vector2Int& camera);
	void Draw(const Vector2Int& num, const Vector2Int& camera);
private:
	void SetDraw(const Vector2Int& center);
};

