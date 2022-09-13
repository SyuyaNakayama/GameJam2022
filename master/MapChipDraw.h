#pragma once
#include "ChipDraw.h"
#include "BreakEffecter.h"
#include "DustEffecter.h"
#include "ArrowEffecter.h"
#include "BrightEffecter.h"
#include "CoinEffecter.h"
#include "CrystalEffecter.h"

class MapChipDraw
{
private:
	ChipDraw blocks[10][10];
	DustEffecter dustE;
	BreakEffecter breakE;
	ArrowEffecter arrowE;
	BrightEffecter brightE;
	CoinEffecter coinE;
	CrystalEffecter crystalE;

	int planeG[3]{};
	int goldG;
	int oreG;
	int bombG;
	int soilG;
	Vector2Int* leftTop;
	int brightness;
	Vector2Int* playerPos;
	Camera* pCamera;
public:
	MapChipDraw();
	void Load();
	void Reset();

	void ChipInit(const Vector2Int& num, const int blockName);
	void ChipBreak(const Vector2Int& num);
	void ChipBright();

	void Update();

	void EraseArrowAndBright(const Vector2Int& num);
	void ClearArrowAndBright();
	void ClearArtifact();

	void CreateArrow(const Vector2Int& num, const int direction);
	void EraseArrow(const Vector2Int& num);
	void ClearArrow();

	void CreateBright(const Vector2Int& num);
	void EraseBright(const Vector2Int& num);
	void ClearBright();

	void Draw(const Vector2Int& camera);
public:

	void SetLeftTop(Vector2Int* leftTop);
	void SetBrightness(const int brightness);
	void SetPlayerPos(Vector2Int* playerPos);
	void SetCamera(Camera* pCamera);
};