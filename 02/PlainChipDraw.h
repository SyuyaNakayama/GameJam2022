#pragma once
#include "Vector2.h"
#include <vector>

struct PlainChipState
{
	Vector2Int pos;

};

class PlainChipDraw
{
private:
	std::vector<PlainChipState> blocks;
	int planeG[3];
public:
	void Load();
	void Update();
	void Draw();
};

