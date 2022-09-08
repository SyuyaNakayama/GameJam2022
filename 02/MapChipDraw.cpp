#include "MapChipDraw.h"
#include "DxLib.h"

void MapChipDraw::Load()
{

	goldG = LoadGraph("Resources/Block/gold.png");
	oreG = LoadGraph("Resources/Block/ore.png");
	oreG = LoadMask("Resources/Block/ore_mask.png");
}

void MapChipDraw::Draw()
{

}
