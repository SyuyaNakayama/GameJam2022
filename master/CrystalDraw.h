#pragma once
#include "Vector2.h"
#include "Ease.h"

class CrystalDraw
{
private:
	struct CrystalLigth
	{
		int trans = 0;
		Ease2 ease;
		bool light = false;
	};
	int* pCrstNum = nullptr;
	CrystalLigth crsts[3];
	int crystalG[2]{};
public:
	void Load();
	void SetCrystalNum(int* crystalNum);
	void Initialize();
	void Update();
	void Draw(const Vector2Int& pos, const Vector2Int& camera);
};

