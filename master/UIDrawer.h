#pragma once
#include "PickelDraw.h"
#include "CashDraw.h"
#include "CrystalDraw.h"

class UIDrawer
{
private:
	PickelDraw pickel;
	CashDraw cash;
	CrystalDraw crystal;
public:
	void LoadAndSet(int* actionNum, int* coinCount, int* crystalNum);
	void Initialize();
	void Update();
	void Draw(const Vector2Int& camera);
};

