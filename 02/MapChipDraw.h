#pragma once
#include "ChipDraw.h"
#include <vector>

class MapChipDraw
{
public:
	enum BlockName
	{
		None,
		Block,
		Coin,
		Crystal,
	};
//private:
	std::vector<ChipDraw> blocks;
	int planeG[3];
	int goldG;
	int oreG;
	int oreMaskG;
	Camera* pCamera;
public:
	MapChipDraw();
	void Load();
	void Draw(const Vector2Int& camera);
	void SetCamera(Camera* pCamera);
};