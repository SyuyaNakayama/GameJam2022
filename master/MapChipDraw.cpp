#include "MapChipDraw.h"
#include "Random.h"
#include "enum.h"

MapChipDraw::MapChipDraw() :
	goldG(0), oreG(0), oreMaskG(0), whiteG(0), bombG(0),
	leftTop(nullptr), brightness(5), playerPos(nullptr), pCamera(nullptr)
{}

void MapChipDraw::Load()
{
	LoadDivGraph("Resources/Block/plane.png", 3, 3, 1, 64, 64, planeG);
	goldG = LoadGraph("Resources/Block/gold.png");
	oreG = LoadGraph("Resources/Block/ore.png");
	whiteG = LoadGraph("Resources/Block/white.png");
	bombG = LoadGraph("Resources/Block/bomb.png");
	breakE.Load();
	dustE.Load();
	arrowE.Load();
	
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
	breakE.Update();
	dustE.Update();
	arrowE.Update();
}

void MapChipDraw::ChipInit(const Vector2Int& num, const int blockName)
{
	int g = 0;
	bool
		isCrystalBlock = false,
		isBombBlock = false,
		death = false;
	switch (blockName)
	{
	case Block:
		g = planeG[GetRand(0, 2)];
		break;
	case CoinBlock:
		g = goldG;
		break;
	case CrystalBlock:
		g = oreG;
		isCrystalBlock = true;
		break;
	case BombBlock:
		g = bombG;
		break;
	case None:
		death = true;
		break;
	}

	blocks[num.y][num.x].Initialze(*leftTop, num, blockName, death, g);
	dustE.Emit(num, blockName);
	if (isCrystalBlock) blocks[num.y][num.x].SetMask(oreMaskG, whiteG);
}

void MapChipDraw::ChipBreak(const Vector2Int& num)
{
	blocks[num.y][num.x].Break();
	breakE.Emit(num, blocks[num.y][num.x].GetType());
}

void MapChipDraw::ChipBright(const Vector2Int& num)
{
	if (blocks[num.y][num.x].GetType() != CrystalBlock) return;
	blocks[num.y][num.x].Bright();
}

void MapChipDraw::CreateArrow(const Vector2Int& num, const int direction)
{
	arrowE.Emit(num, direction, &brightness, playerPos);
}

void MapChipDraw::EraseArrow(const Vector2Int& num)
{
	if ( blocks[num.y][num.x].GetType() == BombBlock) arrowE.Erase(num);
}

void MapChipDraw::CrearArrow()
{
	arrowE.Crear();
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
	breakE.Draw(camera);
	dustE.Draw(camera);
	arrowE.Draw(camera);
}

void MapChipDraw::SetLeftTop(Vector2Int* leftTop)
{
	if (leftTop == nullptr) return;
	this->leftTop = leftTop;
	breakE.SetLeftTop(leftTop);
	dustE.SetLeftTop(leftTop);
	arrowE.SetLeftTop(leftTop);
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
	arrowE.SetPlayerPos(playerPos);
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
