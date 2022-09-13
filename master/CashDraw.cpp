#include "CashDraw.h"
#include "DxLib.h"

void CashDraw::Load()
{
	coinG = LoadGraph("Resources/coin.png");
}

void CashDraw::SetCoinCount(int* coinCount)
{
	if (!coinCount) return;
	pCoinCount = coinCount;
}

void CashDraw::Initialize()
{
	elderNum = *pCoinCount;
	coins.clear();
	count = 0;
	timer = 0;
}

void CashDraw::Update()
{
	if (!pCoinCount) return;
	if (*pCoinCount > elderNum) count = *pCoinCount - elderNum;
	Emit();
	Move();
	elderNum = *pCoinCount;
}

void CashDraw::Emit()
{
	if (count > 0)
	{
		if (++timer < 10) return;
		CoinCount c;
		c.height = -96;
		c.ease.Initialize(0.1f);
		coins.push_back(c);
		timer = 0;
		count--;
		if (count <= 0) count = 0;
	}
}

void CashDraw::Move()
{
	if (coins.empty()) return;
	for (size_t i = 0; i < coins.size(); i++)
	{
		coins[i].ease.Update(true);
		coins[i].height = (int)coins[i].ease.In(-96.0f, 0.0f, 2.0f);
		coins[i].trans = (int)coins[i].ease.In(0.0f, 255.0f, 2.0f);
	}
}

void CashDraw::DrawCoins(const Vector2Int& pos, const Vector2Int& camera)
{
	if (coins.empty()) return;
	for (size_t i = 0; i < coins.size(); i++)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, coins[i].trans);
		DrawGraph(pos.x, pos.y + coins[i].height, coinG, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

void CashDraw::Draw(const Vector2Int& pos, const Vector2Int& camera)
{
	DrawCoins(pos, camera);
	DrawGraph(pos.x, pos.y, coinG, true);
}
