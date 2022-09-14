#include "MapChipDraw.h"
#include "Random.h"
#include "enum.h"

MapChipDraw::MapChipDraw() :
	goldG(0), oreG(0), bombG(0), soilG(0),
	leftTop(nullptr), brightness(0), playerPos(nullptr), pCamera(nullptr)
{}

void MapChipDraw::Load()
{
	LoadDivGraph("Resources/Block/plane.png", 3, 3, 1, 64, 64, planeG);
	goldG = LoadGraph("Resources/Block/gold.png");
	oreG = LoadGraph("Resources/Block/ore.png");
	bombG = LoadGraph("Resources/Block/bomb.png");
	soilG = LoadGraph("Resources/soil.png");
	dustE.Load();
	breakE.Load();
	arrowE.Load();
	brightE.Load();
	coinE.Load();
	crystalE.Load();
	sound = SoundManager::GetInstance();
	for (size_t y = 0; y < 10; y++)
	{
		for (size_t x = 0; x < 10; x++)
		{
			blocks[y][x].SetBrightness(&brightness);
		}
	}
}

void MapChipDraw::Reset()
{
	//dustE.Initialize();
	//breakE.Initialize();
	arrowE.Initialize();
	brightE.Initialize();
	ClearArtifact();
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
	dustE.Update();
	breakE.Update();
	arrowE.Update();
	brightE.Update();
	coinE.Update();
	crystalE.Update();
}

void MapChipDraw::ChipInit(const Vector2Int& num, const int blockName)
{
	int g = 0;
	bool death = false;
	switch (blockName)
	{
	case Block:
		g = planeG[GetRand(0, 2)];
		sound->PlaySE(4);
		break;
	case CoinBlock:
		sound->PlaySE(4);
		g = goldG;
		break;
	case CrystalBlock:
		sound->PlaySE(4);
		g = oreG;
		break;
	case BombBlock:
		sound->PlaySE(4);
		g = bombG;
		break;
	case None:
		death = true;
		break;
	}

	blocks[num.y][num.x].Initialze(*leftTop, num, blockName, death, g);
	dustE.Emit(num, blockName);
}

void MapChipDraw::ChipBreak(const Vector2Int& num)
{
	blocks[num.y][num.x].Break();
	int t = blocks[num.y][num.x].GetType();
	breakE.Emit(num, t);
	sound->PlaySE(0);
	if (t == CoinBlock)
	{
		sound->PlaySE(2);
		sound->PlaySE(3);
		coinE.Emit(num);
	}
	if (t == CrystalBlock)
	{
		sound->PlaySE(2);
		sound->PlaySE(3);
		crystalE.Emit(num);
	}
}

void MapChipDraw::ChipBright()
{
	brightE.Bright();
}

void MapChipDraw::EraseArrowAndBright(const Vector2Int& num)
{
	EraseArrow(num);
	EraseBright(num);
}
void MapChipDraw::ClearArrowAndBright()
{
	ClearArrow();
	ClearBright();
}

void MapChipDraw::ClearArtifact()
{
	coinE.Clear();
	crystalE.Clear();
}

void MapChipDraw::CreateArrow(const Vector2Int& num, const int direction)
{
	if (blocks[num.y][num.x].GetType() == BombBlock) arrowE.Emit(num, direction, &brightness, playerPos);
}
void MapChipDraw::EraseArrow(const Vector2Int& num)
{
	if (blocks[num.y][num.x].GetType() == BombBlock) arrowE.Erase(num);
}
void MapChipDraw::ClearArrow()
{
	arrowE.Clear();
}

void MapChipDraw::CreateBright(const Vector2Int& num)
{
	if (blocks[num.y][num.x].GetType() == CrystalBlock) brightE.Emit(num);
}
void MapChipDraw::EraseBright(const Vector2Int& num)
{
	if (blocks[num.y][num.x].GetType() == CrystalBlock) brightE.Erase(num);
}
void MapChipDraw::ClearBright()
{
	brightE.Clear();
}

void MapChipDraw::Draw(const Vector2Int& camera)
{
	for (size_t y = 0; y < 10; y++)
	{
		for (size_t x = 0; x < 10; x++)
		{
			DrawGraph(
				leftTop->x + (x * 64) - 32 + camera.x,
				leftTop->y + (y * 64) - 32 + camera.y,
				soilG, true);
			blocks[y][x].Draw(camera);
		}
	}
	coinE.Draw(camera);
	crystalE.Draw(camera);
	dustE.Draw(camera);
	breakE.Draw(camera);
	arrowE.Draw(camera);
	brightE.Draw(camera);
}

void MapChipDraw::SetLeftTop(Vector2Int* leftTop)
{
	if (leftTop == nullptr) return;
	this->leftTop = leftTop;
	dustE.SetLeftTop(leftTop);
	breakE.SetLeftTop(leftTop);
	arrowE.SetLeftTop(leftTop);
	brightE.SetLeftTop(leftTop);
	coinE.SetLeftTop(leftTop);
	crystalE.SetLeftTop(leftTop);
}

void MapChipDraw::SetBrightness(const int brightness)
{
	this->brightness = brightness;
	if (this->brightness >= 20) this->brightness = 20;
	if (this->brightness <= 4) this->brightness = 4;
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
