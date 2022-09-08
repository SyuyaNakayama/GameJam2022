#include "PlainChipDraw.h"
#include "DxLib.h"

void PlainChipDraw::Load()
{
	planeG[0] = LoadGraph("Resources/Block/plane_1.png");
	planeG[1] = LoadGraph("Resources/Block/plane_2.png");
	planeG[2] = LoadGraph("Resources/Block/plane_3.png");
}
