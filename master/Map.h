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
	array<array<BlockName, 10>, 10> map{ {} };
	array<array<bool, 10>, 10> isBreak{ {} };
	Vector2Int	pos = { 672,300 };
	int	chipRad = 32;
	Color color;
	vector<Bomb> bomb;
	int stage = 0;
	bool isNext = false;
	bool isChangeOk = false;

	bool countStartFlag = false;
	int respawnTimer = 0;
	int respawnTimerLimit = 120;

	int currentCoin = 0;
	int elderCoin = 0;
	const int COIN_NUM = 7;
	const int BONUS_COIN_NUM = 26;

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

	// --- チュートリアル --- //

	//tutorial Block
	const vector<Vector2Int>tB =
	{
		{4,1},{5,0},{6,1},{5,1},{4,2}
	};

	//ボーナスステージ用マップ(固定)

	//bonus Stage Bomb
	const vector<Vector2Int>bSB =
	{
		{0,0},{0,4},{0,9},{5,0},{5,4},{5,9},{9,4},{9,9}
	};

	//bonus Stage Crystal
	const vector<Vector2Int>bSC =
	{
		{0,5},{4,9},{9,0}
	};

	//bonus Stage Coin Gold
	const vector<Vector2Int>bSCG =
	{
		{1,0},{2,0},{3,0},{4,0},{6,0},{7,0},{8,0},
		{0,1},{0,2},{0,3},
		{6,4},{7,4},{8,4},
		{0,6},{0,7},{0,8},
		{9,5},{9,6},{9,7},{9,8},
		{1,9},{2,9},{3,9},{6,9},{7,9},{8,9}
	};

	Vector2Int* playerPos = nullptr;
public:
	MapChipDraw drawer;
	BreakBlockList bbList;
	int breakCount = 0;
	int scoreCoin = 0;
	int crystalCounter = 0;
public:
	void LoadAndSet();
	void SetOutSide(Camera* camera, Vector2Int* playerPos);
	void Initialize();
	void Reset(); // マップをBlockで初期化
	void Create(const bool init = false);
	void CreateTutorial();
	void NextStage();

	void Update();
	void Change(Vector2Int num, BlockName blockName);
	void Respawn();
	void BreakBlock(const Vector2Int& num, const bool bomb = false);
	void BombDestroy(int bombIndex, Player* player);
	void EraseBomb(const int num);
	void Draw(const Vector2Int& camera);
private:
	void RespawnTimerUpdate();
	void NextPreparation();
public:
	Vector2Int GetMapPos() { return pos; }
	Vector2Int GetChipPos(Vector2Int chipNum) { return pos + 2 * chipRad * chipNum; }
	int GetRadius() { return chipRad; }
	int GetBombBreakCount() { return bbList.GetBombBreak(); }
	Vector2Int GetMapSize() { return { (int)map[0].size(),(int)map.size() }; }
	BlockName GetMapState(Vector2Int pos) { return map[pos.y][pos.x]; }
	vector<Bomb> GetBomb() { return bomb; }
	int GetStage() { return stage; }
	size_t CountBlockNum(BlockName blockName);
	bool IsChangeOk() { return isChangeOk; }

	int CrystalRemain() { return 3 - CountBlockNum(CrystalBlock); }
	int CoinUpdate();
};