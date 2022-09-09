#include "MapChipDraw.h"
#include "DxLib.h"
#include "Random.h"

MapChipDraw::MapChipDraw() :
	goldG(0), oreG(0), oreMaskG(0), pCamera(nullptr)
{
	for (size_t i = 0; i < 3; i++)
	{
		planeG[i] = 0;
	}
	for (size_t i = 0; i < 2; i++)
	{
		debriG[i] = 0;
	}
}

void MapChipDraw::Load()
{
	planeG[0] = LoadGraph("Resources/Block/plane_1.png");
	planeG[1] = LoadGraph("Resources/Block/plane_2.png");
	planeG[2] = LoadGraph("Resources/Block/plane_3.png");
	goldG = LoadGraph("Resources/Block/gold.png");
	oreG = LoadGraph("Resources/Block/ore.png");
	debriG[0] = LoadGraph("Resources/Block/debri.png");
	debriG[1] = LoadGraph("Resources/Block/debri2.png");

	oreMaskG = LoadMask("Resources/Block/ore_mask.png");
}

void MapChipDraw::Update()
{
	for (size_t y = 0; y < 10; y++)
	{
		for (size_t x = 0; x < 10; x++)
		{
			blocks[y][x].Update();
		}
	}
}

void MapChipDraw::ChipInit(const int x, const int y)
{
	int g[2];

	//g = planeG[GetRand(0, 2)];
	//g = goldG;
	g[0] = oreG;
	//g = oreMaskG;

	//g[1] = debriG[0];
	g[1] = debriG[1];

	blocks[y][x].Initialze({ 200,500 }, { x, y }, ChipDraw::BlockType::Ore, g[0], g[1]);
}

void MapChipDraw::ChipBreak(const int x, const int y)
{
	blocks[y][x].Break();
}

void MapChipDraw::Draw(const Vector2Int& camera)
{
	for (size_t y = 0; y < 10; y++)
	{
		for (size_t x = 0; x < 10; x++)
		{
			blocks[y][x].Draw(camera);
		}
	}
}

void MapChipDraw::SetCamera(Camera* pCamera)
{
	if (pCamera == nullptr) return;
	this->pCamera = pCamera;
	for (size_t y = 0; y < 10; y++)
	{
		for (size_t x = 0; x < 10; x++)
		{
			blocks[y][x].SetCamera(pCamera);
		}
	}
}
