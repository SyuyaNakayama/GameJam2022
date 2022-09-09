#include "MapChipDraw.h"
#include "DxLib.h"
#include "Random.h"
#include "enum.h"

MapChipDraw::MapChipDraw() :
	goldG(0), oreG(0), oreMaskG(0), whiteG(0), bombG(0), arrowG(0),
	brightness(5), playerPos(nullptr), pCamera(nullptr)
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
	whiteG = LoadGraph("Resources/Block/white.png");
	bombG = LoadGraph("Resources/Block/bomb.png");
	arrowG = LoadGraph("Resources/Block/arrow.png");
	debriG[0] = LoadGraph("Resources/Block/debri.png");
	debriG[1] = LoadGraph("Resources/Block/debri2.png");

	oreMaskG = LoadMask("Resources/Block/ore_mask.png");

	for (size_t y = 0; y < 10; y++)
	{
		for (size_t x = 0; x < 10; x++)
		{
			blocks[y][x].SetBrightness(&brightness);
		}
	}
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

void MapChipDraw::ChipInit(const int x, const int y, const int blockName)
{
	if (playerPos != nullptr)
	{
		if (playerPos->x == x && playerPos->y == y) return;
	}

	int g[2] = { 0, 0 };
	bool b = false;
	bool b2 = false;
	switch (blockName)
	{
	case Block:
		g[0] = planeG[GetRand(0, 2)];
		g[1] = debriG[0];
		break;
	case CoinBlock:
		g[0] = goldG;
		g[1] = debriG[1];
		break;
	case CrystalBlock:
		g[0] = oreG;
		g[1] = debriG[1];
		b = true;
		break;
	case BombBlock:
		g[0] = bombG;
		g[1] = debriG[0];
		b2 = true;
		break;
	case None:
	default:
		break;
	}
	blocks[y][x].Initialze({ 200,500 }, { x, y }, blockName, g[0], g[1]);
	if (b) blocks[y][x].SetMask(oreMaskG, whiteG);
	if (b2) blocks[y][x].SetArrow(Up, arrowG);
}

void MapChipDraw::ChipBreak(const int x, const int y)
{
	blocks[y][x].Break();
}

void MapChipDraw::ChipBright(const int x, const int y)
{
	if(blocks[y][x].GetType() != CrystalBlock) return;
	blocks[y][x].Bright();
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

void MapChipDraw::SetBrightness(const int brightness)
{
	this->brightness = brightness;
	if (this->brightness >= 20) this->brightness = 20;
	if (this->brightness <= 0) this->brightness = 0;
}

void MapChipDraw::SetPlayerPos(Vector2Int* playerPos)
{
	if (playerPos == nullptr) return;
	this->playerPos = playerPos;
	for (size_t y = 0; y < 10; y++)
	{
		for (size_t x = 0; x < 10; x++)
		{
			blocks[y][x].SetPlayerPos(playerPos);
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
