#include "CrystalDraw.h"
#include "DxLib.h"

void CrystalDraw::Load()
{
	LoadDivGraph("Resources/crystal.png", 2, 2, 1, 64, 64, crystalG);
}

void CrystalDraw::SetCrystalNum(int* crystalNum)
{
	if (!crystalNum) return;
	pCrstNum = crystalNum;
}

void CrystalDraw::Initialize()
{
	for (size_t i = 0; i < 3; i++)
	{
		crsts[i].ease.Initialize(0.1f, 0.1f);
	}
}

void CrystalDraw::Update()
{
	if (!pCrstNum) return;
	for (size_t i = 0; i < 3; i++)
	{
		crsts[i].light = (*pCrstNum > i);
		crsts[i].ease.Update(crsts[i].light);
		crsts[i].trans = crsts[i].ease.In(0.0f, 255.0f, 2.0f);
	}
}

void CrystalDraw::Draw(const Vector2Int& pos, const Vector2Int& camera)
{
	for (size_t i = 0; i < 3; i++)
	{
		DrawGraph(pos.x, pos.y - (96 * i), crystalG[1], true);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, crsts[i].trans);
		DrawGraph(pos.x, pos.y - (96 * i), crystalG[0], true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}
