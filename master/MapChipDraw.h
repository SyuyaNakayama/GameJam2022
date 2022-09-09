#pragma once
#include "ChipDraw.h"

class MapChipDraw
{
private:
	ChipDraw blocks[10][10];
	int planeG[3];
	int goldG;
	int oreG;
	int oreMaskG;
	int whiteG;
	int bombG;
	int arrowG;
	int debriG[2];
	int brightness;
	Vector2Int* playerPos;
	Camera* pCamera;
public:
	MapChipDraw();
	void Load();
	void Update();
	void ChipInit(const int x, const int y, const int blockName);
	void ChipBreak(const int x, const int y);
	void ChipBright(const int x, const int y);
	void Draw(const Vector2Int& camera);
	void SetBrightness(const int brightness);
	void SetPlayerPos(Vector2Int* playerPos);
	void SetCamera(Camera* pCamera);
};