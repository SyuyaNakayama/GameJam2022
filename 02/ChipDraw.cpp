#include "ChipDraw.h"
#include "DxLib.h"

ChipDraw::ChipDraw() :
	pos({ -256,-256 }), height(0), ease(), 
	dustE(), isLanding(false), isEmit(false), 
	trans(0), graph(0), pCamera(nullptr)
{}

void ChipDraw::Initialze(const Vector2Int& leftTop, const Vector2Int& ary, const int graph)
{
	pos = { leftTop.x + ary.x * 64, leftTop.y + ary.y * 64 };
	height = 0;
	ease.Initialize(0.05f);
	isLanding = false;
	isEmit = false;
	trans = 0;
	this->graph = graph;
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
	trans = (int)ease.Out(0.0f, 255.0f, 2.0f);
}

void ChipDraw::Draw(const Vector2Int& camera)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, trans);
	DrawGraph(pos.x - 32 + camera.x, pos.y + height - 32 + camera.y, graph, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	dustE.Draw(camera);
}

void ChipDraw::Landing()
{
	dustE.Emit({ pos.x - 32, pos.y - 32 }, { pos.x + 32, pos.y + 32 }, 10);
	if (pCamera == nullptr) return;
	pCamera->Shaking(5, 1);
}

void ChipDraw::SetCamera(Camera* pCamera)
{
	if (pCamera == nullptr) return;
	this->pCamera = pCamera;
}
