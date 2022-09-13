#pragma once
#include "ChipDraw.h"
#include "BreakEffecter.h"
#include "DustEffecter.h"
#include "ArrowEffecter.h"
#include "BrightEffecter.h"

class MapChipDraw
{
private:
	ChipDraw blocks[10][10];
	DustEffecter dustE;
	BreakEffecter breakE;
	ArrowEffecter arrowE;
	BrightEffecter brightE;
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
	void Update();
	void ChipInit(const Vector2Int& num, const int blockName);
	void ChipBreak(const Vector2Int& num);
	void ChipBright();

	void EraseArrowAndBright(const Vector2Int& num);
	void ClearArrowAndBright();

	void CreateArrow(const Vector2Int& num, const int direction);
	void EraseArrow(const Vector2Int& num);
	void CrearArrow();

	void CreateBright(const Vector2Int& num);
	void EraseBright(const Vector2Int& num);
	void CrearBright();

	void Draw(const Vector2Int& camera);
	void SetLeftTop(Vector2Int* leftTop);
	void SetBrightness(const int brightness);
	void SetPlayerPos(Vector2Int* playerPos);
	void SetCamera(Camera* pCamera);
};