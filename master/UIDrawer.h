#pragma once
#include "PickelDraw.h"
#include "CashDraw.h"
#include "CrystalDraw.h"
#include "Input.h"
#include "Font.h"

class UIDrawer
{
private:
	PickelDraw pickel;
	CashDraw cash;
	CrystalDraw crystal;
	Input* input = nullptr;
	Font* font = nullptr;

	int* pActNum = nullptr;
	int* pCoinCount = nullptr;
public:
	void LoadAndSet(int* actionNum, int* coinCount, int* crystalNum);
	void Initialize();
	void Update();
	void DrawTitle();
	void DrawPro(const Vector2Int& camera);
	void DrawTutorial(const Vector2Int& camera, const int bombCount);
	void DrawPlay(const Vector2Int& camera, const int bombCount, const int stage);
	void DrawMenu();
	void DrawResult(const int offset);
};

