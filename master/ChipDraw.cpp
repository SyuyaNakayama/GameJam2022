#include "ChipDraw.h"
#include "enum.h"
#include <math.h>

ChipDraw::ChipDraw() :
	pos({ -256,-256 }), height(0), ease(), type(None),
	dustE(), isLanding(false), isEmit(false), 
	debriE(), shake(), isBreak(false), isEmit2(false),
	bright(), arrow(), isDeath(false),
	trans(255), shadow(255), brightness(nullptr),
	blockG(0), debriG(0),
	pCamera(nullptr), playerPos(nullptr)
{}

void ChipDraw::Initialze(const Vector2Int& leftTop, const Vector2Int& ary, 
		const int type, const bool isDeath,
		const int blockG, const int debriG)
{
	pos = { leftTop.x + ary.x * 64, leftTop.y + ary.y * 64 };
	number = ary;
	height = 0;
	ease.Initialize(0.05f);
	this->type = type;
	this->isDeath = isDeath;
	isLanding = false;
	isEmit = false;
	shake.Initialize();
	isBreak = false;
	isEmit2 = false;
	trans = 255;
	shadow = 0;
	this->blockG = blockG;
	this->debriG = debriG;
}

void ChipDraw::SetMask(const int maskG, const int whiteG)
{
	bright.Initialize({ 64,64 }, maskG, whiteG);
}

void ChipDraw::SetArrow(const int direction, const int arrowG)
{
	arrow.Initialize(direction, arrowG);
}

void ChipDraw::Update()
{
	if (!isDeath)
	{
		ease.Update(true);
		height = (int)ease.In(-160.0f, 0.0f, 3.0f);
		if (height == 0) isLanding = true;
		if (isLanding && !isEmit)
		{
			Landing();
			isLanding = false;
			isEmit = true;
		}
		dustE.Update();

		shake.Update();
		if (!shake.IsShake() && isBreak) isEmit2 = true;
		if (isEmit2)
		{
			EmitDebris();
			isBreak = false;
			isEmit2 = false;
		}
		debriE.Update();
		if (debriE.GetIsDeath())
		{
			isDeath = true;
			type = None;
		}

		if (type == CrystalBlock) bright.Update();
		//if (type == BombBlock) arrow.Update();

		trans = (int)ease.Out(0.0f, 255.0f, 2.0f);
	}

	UpdateShadow();
}

void ChipDraw::Landing()
{
	dustE.Emit({ pos.x - 32, pos.y - 32 }, { pos.x + 32, pos.y + 32 }, 10);
	if (pCamera == nullptr) return;
	pCamera->Shaking(5, 1);
}

void ChipDraw::Break()
{
	shake.Shaking(10, 2);
	isBreak = true;
	if (pCamera == nullptr) return;
	pCamera->Shaking(5, 1);
}

void ChipDraw::Bright()
{
	bright.Bright();
}

void ChipDraw::EmitDebris()
{
	Debri::Color c[2];
	switch (type)
	{
	case Block:
		c[0] = { 150,210,220 };
		c[1] = { 100,110,140 };
		break;
	case CoinBlock:
		c[0] = { 250,250,100 };
		c[1] = { 130,130,90 };
		break;
	case CrystalBlock:
		c[0] = { 180,250,100 };
		c[1] = { 70,80,110 };
		break;
	case BombBlock:
		c[0] = { 240,170,20 };
		c[1] = { 160,70,40 };
		break;
	case None:
	default:
		break;
	}
	debriE.Emit({ pos.x - 32, pos.y - 32 }, { pos.x + 32, pos.y + 32 }, 20, c, debriG);
}

void ChipDraw::UpdateShadow()
{
	if (playerPos == nullptr) return;
	if (brightness == nullptr) return;

	int x = abs(playerPos->x - number.x);
	int y = abs(playerPos->y - number.y);

	int p = 0;
	if (x >= y) p = x;
	if (x <= y) p = y;

	if (p > *brightness) shadow = 255;
	else shadow = 255 - ((*brightness - p) * 60);

	if (shadow >= 255) shadow = 255;
	if (shadow <= 0) shadow = 0;
}

void ChipDraw::DrawShadow(const Vector2Int& camera)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, shadow);
	DrawBox(pos.x - 32 + camera.x, pos.y - 32 + camera.y,
			pos.x + 32 + camera.x, pos.y + 32 + camera.y,
			GetColor(0, 0, 0), true);
}

void ChipDraw::Draw(const Vector2Int& camera)
{
	Vector2Int p = 
	{
		pos.x + shake.GetValue().x,
		pos.y + height + shake.GetValue().y 
	};
	bool d = !isDeath;

	if (d) 
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, trans);

		DrawGraph(p.x - 32 + camera.x, p.y - 32 + camera.y, blockG, true);

		if (type == BombBlock) arrow.Draw(p, camera, trans);
	}

	DrawShadow(camera);

	if (d)
	{
		if (type == CrystalBlock) bright.Draw(p, camera, trans);

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		dustE.Draw(camera);
		debriE.Draw(camera);
	}

	DrawFormatString(p.x, p.y, GetColor(0, 0, 255), "%d", type);
}

void ChipDraw::SetBrightness(int* brightness)
{
	if (brightness == nullptr) return;
	this->brightness = brightness;
}

void ChipDraw::SetPlayerPos(Vector2Int* playerPos)
{
	if (playerPos == nullptr) return;
	this->playerPos = playerPos;
}

void ChipDraw::SetCamera(Camera* pCamera)
{
	if (pCamera == nullptr) return;
	this->pCamera = pCamera;
}