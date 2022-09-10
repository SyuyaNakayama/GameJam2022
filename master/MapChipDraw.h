#pragma once
#include "ChipDraw.h"
#include "BreakEffecter.h"

class MapChipDraw
{
private:
	ChipDraw blocks[10][10];
	BreakEffecter breakE;
	int planeG[3]{};
	int goldG;
	int oreG;
	int oreMaskG;
	int whiteG;
	int bombG;
	int arrowG;
	Vector2Int* leftTop;
	int brightness;
	Vector2Int* playerPos;
	Camera* pCamera;
public:
	MapChipDraw();
	void Load();
	void Update();
	void ChipInit(const Vector2Int& num, const int blockName, const int direction = 0);
	void ChipBreak(const Vector2Int& num);
	void ChipBright(const Vector2Int& num);
	void Draw(const Vector2Int& camera);
	void SetLeftTop(Vector2Int* leftTop);
	void SetBrightness(const int brightness);
	void SetPlayerPos(Vector2Int* playerPos);
	void SetCamera(Camera* pCamera);
};