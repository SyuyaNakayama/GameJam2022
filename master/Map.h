#pragma once
#include <array>
#include <vector>
#include <list>
#include "DxLib.h"
#include "Player.h"
#include "enum.h"
#include "Bomb.h"

using namespace std;

class Map
{
private:
	array<array<BlockName, 10>, 10>map;
	Vector2Int	pos = { 500,200 };
	int	chipRad = 32;
	Color color;
	list<Bomb> bomb;

	const vector<vector<Vector2Int>>crystalPos =
	{
		{{2,1},{4,9},{8,3}},
		{{0,9},{3,0},{6,5}},
		{{0,4},{9,0},{9,9}},
		{{0,0},{2,8},{9,7}},
		{{0,8},{6,0},{9,5}},
		{{3,6},{7,8},{8,0}},
		{{0,7},{6,2},{9,8}},
		{{1,2},{8,9},{9,2}},
		{{1,8},{2,9},{8,1}}
	};
	const int COIN_NUM = 7;
	int crystalPattern;
public:
	Vector2Int GetMapPos() { return pos; }
	Vector2Int GetChipPos(Vector2Int chipNum) { return pos + 2 * chipRad * chipNum; }
	int GetRadius() { return chipRad; }
	Vector2Int GetMapSize();
	BlockName GetMapState(Vector2Int pos);
	list<Bomb> GetBomb() { return bomb; }
	size_t CountBlockNum(BlockName blockName);

	Map() { Init(); }
	void Init(); // É}ÉbÉvÇBlockÇ≈èâä˙âª
	void Change(Vector2Int num, BlockName blockName);
	void Create();
	void Draw();
	void BombDestroy(int bombIndex);
private:
	const vector<int>CHIP_COLOR = { color.Black,color.White,color.Yellow,color.Green,color.Red };
};