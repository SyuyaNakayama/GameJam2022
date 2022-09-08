#pragma once
#include <vector>
#include "DxLib.h"
#include "Player.h"

using namespace std;

enum BlockName { None, Block, CoinBlock, Coin, CrystalBlock, Crystal };
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
	vector<vector<BlockName>>map;
	Vector2Int	pos = { 500,200 };
	int	chipRad = 32;
	Color color;
public:
	Map(Vector2Int num);

	void SetMapPos(Vector2Int pos_) { pos = pos_; }
	void SetRadius(int radius) { chipRad = radius; }
	void SetMapSize(Vector2Int num);

	Vector2Int GetMapPos() { return pos; }
	Vector2Int GetChipPos(Vector2Int chipNum) { return pos + 2 * chipRad * chipNum; }
	int GetRadius() { return chipRad; }
	Vector2Int GetMapSize();
	BlockName GetMapState(Vector2Int pos) { return map[pos.y][pos.x]; }

	void MapInit(); // É}ÉbÉvÇNoneÇ≈èâä˙âª
	void Change(Vector2Int num, BlockName blockName);
	void Draw();
private:
	const vector<int>CHIP_COLOR = { color.Black,color.White,color.Green,color.Red };
};