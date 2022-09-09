#pragma once
#include "ChipDraw.h"

class MapChipDraw
{
public:
	enum BlockType
	{
		None,
		Plain,
		Gold,
		Ore,
		Bomb,
	};
private:
	ChipDraw blocks[10][10];
	int planeG[3];
	int goldG;
	int oreG;
	int oreMaskG;
	int debriG[2];
	Camera* pCamera;
public:
	MapChipDraw();
	void Load();
	void Update();
	void Draw(const Vector2Int& camera);
	void SetCamera(Camera* pCamera);
//private:
	void ChipInit(const int x, const int y);
	void ChipBreak(const int x, const int y);
};