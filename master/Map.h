#pragma once
#include <array>
#include <vector>
#include <list>
#include "DxLib.h"
#include "Player.h"
#include "enum.h"
#include "Bomb.h"
#include "BreakBlockList.h"
#include "MapChipDraw.h"

using namespace std;

class Player;

class Map
{
private:
	array<array<BlockName, 10>, 10>map;
	Vector2Int	pos = { 500,200 };
	int	chipRad = 32;
	Color color;
	vector<Bomb> bomb;
	int stage = 1;

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
	const vector<int>CHIP_COLOR = { color.Black,color.White,color.Yellow,color.Green,color.Red };
public:
	MapChipDraw drawer;
	BreakBlockList bbList;

	Map() { LoadAndSet(); Init(); }
	
	Vector2Int GetMapPos() { return pos; }
	Vector2Int GetChipPos(Vector2Int chipNum) { return pos + 2 * chipRad * chipNum; }
	int GetRadius() { return chipRad; }
	int GetBombBreakCount() { return bbList.GetBombBreak(); }
	Vector2Int GetMapSize() { return { (int)map[0].size(),(int)map.size() }; }
	BlockName GetMapState(Vector2Int pos) { return map[pos.y][pos.x]; }
	vector<Bomb> GetBomb() { return bomb; }
	int GetStage() { return stage; }

	void Init(); // É}ÉbÉvÇBlockÇ≈èâä˙âª
	void Change(Vector2Int num, BlockName blockName);
	void Create();
	void Respawn();
	void BombDestroy(int bombIndex, Player* player);
	void Draw(const Vector2Int& camera);
	size_t CountBlockNum(BlockName blockName);

	void LoadAndSet();
	void SetBrightness(const int brightness);
	void SetOutSide(Camera* camera, Vector2Int* playerPos);
	void Update();
	void NextStage() { stage++; Create(); }
};