#include "PickelDraw.h"
#include "DxLib.h"

void PickelDraw::Load()
{
	pickelG = LoadGraph("Resources/pickel.png");
	LoadDivGraph("Resources/pickel.png", 2, 1, 2, 64, 32, brokenG);
}

void PickelDraw::SetActNum(int* actionNum)
{
	if (!actionNum) return;
	pActNum = actionNum;
}

void PickelDraw::Initialize()
{
	elderNum = *pActNum;
	pickels.clear();
	count = 0;
	timer = 0;
	shake.Initialize();
}

void PickelDraw::Update()
{
	if (!pActNum) return;
	if (*pActNum < elderNum) count = elderNum - *pActNum;
	Emit();
	Move();
	shake.Update();
	elderNum = *pActNum;
}

void PickelDraw::Emit()
{
	if (count > 0)
	{
		if (++timer < 5) return;
		BrokenPickel p;
		p.sp = { 2,-8 };
		pickels.push_back(p);
		timer = 0;
		count--;
		if (count <= 0) count = 0;
		shake.Shaking(20, 2);
	}
}

void PickelDraw::Move()
{
	if (pickels.empty()) return;
	for (size_t i = 0; i < pickels.size(); i++)
	{
		pickels[i].sp.y += 1;
		pickels[i].pos += pickels[i].sp;
		pickels[i].rota += DX_PI_F / 36;
		if (pickels[i].rota >= 2.0f * DX_PI_F) pickels[i].rota -= 2.0f * DX_PI_F;
		pickels[i].trans -= 10;
		if (pickels[i].trans <= 0) pickels.erase(std::begin(pickels) + i);
	}
}

void PickelDraw::Draw(const Vector2Int& pos, const Vector2Int& camera)
{
	DrawGraph(pos.x + shake.GetValue().x, pos.y + shake.GetValue().y, pickelG, true);

	if (pickels.empty()) return;
	Vector2Int center = { pos.x + 32, pos.y + 32 };
	for (size_t i = 0; i < pickels.size(); i++)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, pickels[i].trans);
		for (size_t j = 0; j < 2; j++)
		{
			int a = 1;
			if (j) a = -1;
			DrawRotaGraph(
				center.x + (pickels[i].pos.x * a) + shake.GetValue().x,
				center.y + pickels[i].pos.y + (32 * j) + shake.GetValue().y, 1.0f,
				(pickels[i].rota * a), brokenG[j], true);
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
