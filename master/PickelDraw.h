#pragma once
#include "Shake.h"
#include <vector>

class PickelDraw
{
private:
	struct BrokenPickel
	{
		Vector2Int pos;
		Vector2Int sp;
		float rota = 0.0f;
		int trans = 255;
	};
	int* pActNum = nullptr;
	int elderNum = 0;
	std::vector<BrokenPickel> pickels;
	int count = 0;
	int timer = 0;
	Shake shake;
	int pickelG = 0;
	int brokenG[2]{};
public:
	void Load();
	void SetActNum(int* actionNum);
	void Initialize();
	void Update();
	void Draw(const Vector2Int& pos, const Vector2Int& camera);
private:
	void Emit();
	void Move();
};

