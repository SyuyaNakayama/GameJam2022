#pragma once
#include <vector>
#include "Vector2.h"
#include "DxLib.h"
#include "Player.h"

using namespace std;

enum BlockName { None, Block, CoinBlock, TreasureBox };
struct Color
{
	const int
		Black = GetColor(0, 0, 0),
		White = GetColor(255, 255, 255),
		Red = GetColor(255, 0, 0),
		Green = GetColor(0, 255, 0),
		Blue = GetColor(0, 0, 255),
		Yellow = GetColor(255, 255, 0);
};

class Map
{
private:
	vector<vector<int>>map;
	Vector2Int	pos = { 500,200 };
	int	mapChipRad = 32;
	Color color;
public:
	Map(Vector2Int num);
	Map() {};
	void SetMapPos(Vector2Int pos_) { pos = pos_; }
	void SetRadius(int radius) { mapChipRad = radius; }
	void SetMapSize(Vector2Int num);
	Vector2Int GetMapPos() { return pos; }
	int GetRadius() { return mapChipRad; }
	Vector2Int GetMapSize();
	Vector2Int GetPlayerMapChip(Player);
	void MapInit(); // É}ÉbÉvÇNoneÇ≈èâä˙âª
	void Change(Vector2Int num, BlockName blockName);
	void Draw(Vector2Int playerPos, float playerAngle);
private:
	const vector<int>CHIP_COLOR = { color.Black,color.White,color.Green,color.Red };
};