#include "SelectDraw.h"
#include "DxLib.h"

void SelectDraw::Load()
{
	setG = LoadGraph("Resources/frame.png");
	lockG = LoadGraph("Resources/lock.png");
}

void SelectDraw::Initialize(const Vector2Int& leftTop)
{
	this->leftTop = leftTop;
	Reset();
}

void SelectDraw::Reset()
{
	locks.clear();
	ease.Initialize(0.075f, 0.075f);
	isEase = true;
}

void SelectDraw::Update()
{
	ease.Update(isEase);

	dist.x = (int)ease.In(32.0f, 16.0f, 2.0f);
	dist.y = (int)ease.In(32.0f, 16.0f, 2.0f);

	if (ease.ratio >= 1.0f) isEase = false;
	if (ease.ratio <= 0.0f) isEase = true;

	if (locks.empty()) return;

	for (size_t i = 0; i < locks.size(); i++)
	{
		locks[i].ease.Update(locks[i].isChose);
		locks[i].rota = locks[i].ease.Out(720.0f, 0.0f, 2.0f);
		locks[i].scale = locks[i].ease.Out(1.5f, 1.0f, 2.0f);
		locks[i].trans = (int)locks[i].ease.In(0.0f, 255.0f, 2.0f);
		if (!locks[i].isChose && locks[i].trans <= 0)
		{
			locks.erase(std::begin(locks) + i);
		}
	}
}

void SelectDraw::CreateChose(const Vector2Int& num, const int number)
{
	ChoseState c;
	c.pos = { leftTop.x + num.x * 64, leftTop.y + num.y * 64 };
	c.number = number;
	c.isChose = true;
	c.ease.Initialize(0.1f, 0.1f);
	locks.push_back(c);
}

void SelectDraw::EraseChose(const int number)
{
	locks[number].isChose = false;
}

void SelectDraw::ClearChose()
{
	for (size_t i = 0; i < locks.size(); i++)
	{
		locks[i].isChose = false;
	}
}

void SelectDraw::ChoseDraw(const Vector2Int& camera)
{
	if (locks.empty()) return;
	for (size_t i = 0; i < locks.size(); i++)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		int n = locks[i].number;
		if (n == 1) SetDrawBright(230, 120, 30);
		if (n == 2) SetDrawBright(230, 170, 30);
		if (n == 3) SetDrawBright(230, 200, 30);
		DrawRotaGraph(locks[i].pos.x, locks[i].pos.y, locks[i].scale, locks[i].rota, lockG, true);
		SetDrawBright(255, 255, 255);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

void SelectDraw::Draw(const Vector2Int& num, const Vector2Int& camera)
{
	Vector2Int center = { leftTop.x + num.x * 64, leftTop.y + num.y * 64 };
	SetDraw(center);
}

void SelectDraw::SetDraw(const Vector2Int& center)
{
	DrawRotaGraph(center.x - dist.x, center.y - dist.y, 1.0f, 0.0f, setG, true);
	DrawRotaGraph(center.x + dist.x, center.y - dist.y, 1.0f, DX_PI_F / 2.0f, setG, true);
	DrawRotaGraph(center.x + dist.x, center.y + dist.y, 1.0f, DX_PI_F, setG, true);
	DrawRotaGraph(center.x - dist.x, center.y + dist.y, 1.0f, DX_PI_F * 1.5f, setG, true);
}
