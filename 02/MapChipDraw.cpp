#include "MapChipDraw.h"
#include "DxLib.h"

MapChipDraw::MapChipDraw() :
	goldG(0), oreG(0), oreMaskG(0), pCamera(nullptr)
{
	for (size_t i = 0; i < 3; i++)
	{
		planeG[i] = 0;
	}
}

void MapChipDraw::Load()
{
	planeG[0] = LoadGraph("Resources/Block/plane_1.png");
	planeG[1] = LoadGraph("Resources/Block/plane_2.png");
	planeG[2] = LoadGraph("Resources/Block/plane_3.png");
	goldG = LoadGraph("Resources/Block/gold.png");
	oreG = LoadGraph("Resources/Block/ore.png");
	oreG = LoadMask("Resources/Block/ore_mask.png");
}

void MapChipDraw::Draw(const Vector2Int& camera)
{

}

void MapChipDraw::SetCamera(Camera* pCamera)
{
	if (pCamera == nullptr) return;
	this->pCamera = pCamera;
}