#include "ChipDraw.h"
#include "DxLib.h"

ChipDraw::ChipDraw() :
	pos({ -256,-256 }), height(0), ease(), type(None),
	dustE(), isLanding(false), isEmit(false), 
	debriE(), shake(), isBreak(false), isEmit2(false),
	trans(0), blockG(0), debriG(0), pCamera(nullptr)
{}

void ChipDraw::Initialze(const Vector2Int& leftTop, const Vector2Int& ary, 
		const int type, const int blockG, const int debriG)
{
	pos = { leftTop.x + ary.x * 64, leftTop.y + ary.y * 64 };
	height = 0;
	ease.Initialize(0.05f);
	this->type = type;
	isLanding = false;
	isEmit = false;
	shake.Initialize();
	isBreak = false;
	isEmit2 = false;
	trans = 255;
	this->blockG = blockG;
	this->debriG = debriG;
}

void ChipDraw::Update()
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
	if(isEmit2)
	{
		EmitDebris();
		isBreak = false;
		isEmit2 = false;
	}
	debriE.Update();
	trans = (int)ease.Out(0.0f, 255.0f, 2.0f);
}

void ChipDraw::Landing()
{
	dustE.Emit({ pos.x - 32, pos.y - 32 }, { pos.x + 32, pos.y + 32 }, 10);
	if (pCamera == nullptr) return;
	pCamera->Shaking(5, 1);
}

void ChipDraw::Break()
{
	shake.Shaking(10.0f, 2.0f);
	isBreak = true;
	if (pCamera == nullptr) return;
	pCamera->Shaking(5, 1);
}

void ChipDraw::EmitDebris()
{
	Debri::Color c[2];
	switch (type)
	{
	case Plain:
		c[0] = { 150,210,220 };
		c[1] = { 100,110,140 };
		break;
	case Gold:
		c[0] = { 250,250,100 };
		c[1] = { 130,130,90 };
		break;
	case Ore:
		c[0] = { 180,250,100 };
		c[1] = { 70,80,110 };
		break;
	case Bomb:
		c[0] = { 150,210,220 };
		c[1] = { 100,110,140 };
		break;
	case None:
	default:
		break;
	}
	debriE.Emit({ pos.x - 32, pos.y - 32 }, { pos.x + 32, pos.y + 32 }, 20, c, debriG);
}

void ChipDraw::Draw(const Vector2Int& camera)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, trans);
	DrawGraph(	pos.x - 32 + shake.GetValue().x + camera.x, 
				pos.y + height - 32 + shake.GetValue().y + camera.y, blockG, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	dustE.Draw(camera);
	debriE.Draw(camera);
}

void ChipDraw::SetCamera(Camera* pCamera)
{
	if (pCamera == nullptr) return;
	this->pCamera = pCamera;
}
