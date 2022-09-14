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
public:
	void LoadAndSet(int* actionNum, int* coinCount, int* crystalNum);
	void Initialize();
	void Update();
	void DrawTutorial(const Vector2Int& camera);
	void DrawPlay(const Vector2Int& camera);
private:
	void DrawInput();
};

