#include "ChipDraw.h"
#include "enum.h"
#include <math.h>
#include "function.h"
#include "EffectParameter.h"

ChipDraw::ChipDraw() :
	pos({ -256,-256 }), height(0), ease(), type(None),
	dustE(), isLanding(false), isEmit(false),
	shake(), isBreak(false),
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
		if (!shake.IsShake() && isBreak) 
		{
			isDeath = true;
			type = None;
		}

		if (type == CrystalBlock) bright.Update();
		if (type == BombBlock) arrow.Update();

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
	shake.Shaking(10, 10 / BreakEffectTime);
	isBreak = true;
	if (!pCamera) return;
	pCamera->Shaking(5, 1);
}

void ChipDraw::Bright()
{
	bright.Bright();
}

void ChipDraw::UpdateShadow()
{
	if (!playerPos || !brightness) return;

	Vector2Int disPandB = Vector2Int(*playerPos - number).absVec();

	int p = 0;
	if (disPandB.x > disPandB.y) p = disPandB.x;
	else p = disPandB.y;

	if (p > *brightness) shadow = 255;
	else shadow = 255 - ((*brightness - p) * 60);

	Clamp(shadow, 255);
}

void ChipDraw::DrawShadow(const Vector2Int& camera)
{
	Color color;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, shadow);
	DrawBoxWithVectorInt(pos + camera, { 32,32 }, color.Black);
}

void ChipDraw::Draw(const Vector2Int& camera)
{
	Vector2Int p =
	{
		pos.x + shake.GetValue().x,
		pos.y + height + shake.GetValue().y
	};

	if (!isDeath)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, trans);

		DrawGraph(p.x - 32 + camera.x, p.y - 32 + camera.y, blockG, true);

		if (type == BombBlock) arrow.Draw(p, camera, trans);
	}

	DrawShadow(camera);

	if (!isDeath)
	{
		if (type == CrystalBlock) bright.Draw(p, camera, trans);

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		dustE.Draw(camera);
	}

	DrawFormatString(p.x, p.y, GetColor(0, 0, 255), "%d", type);
}

void ChipDraw::SetBrightness(int* brightness)
{
	if (!brightness) return;
	this->brightness = brightness;
}

void ChipDraw::SetPlayerPos(Vector2Int* playerPos)
{
	if (!playerPos) return;
	this->playerPos = playerPos;
}

void ChipDraw::SetCamera(Camera* pCamera)
{
	if (!pCamera) return;
	this->pCamera = pCamera;
}
