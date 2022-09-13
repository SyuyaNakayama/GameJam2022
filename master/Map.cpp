#include "Map.h"
#include "function.h"
#include <cassert>

void Map::LoadAndSet()
{
	drawer.Load();
	drawer.SetLeftTop(&pos);
}

void Map::SetOutSide(Camera* camera, Vector2Int* playerPos)
{
	drawer.SetCamera(camera);
	drawer.SetPlayerPos(playerPos);
	this->playerPos = playerPos;
}

void Map::Initialize()
{
	Reset();
	bbList.Initialize();
	stage = 0;
}

void Map::Reset()
{
	for (size_t y = 0; y < map.size(); y++)
	{
		for (size_t x = 0; x < map[y].size(); x++)
		{
			map[y][x] = Block;
			drawer.ChipInit({ (int)x, (int)y }, Block);
		}
	}
	bomb.clear();
	breakCount = 0;

	bbList.Reset();
	drawer.Reset();

	isNext = false;
	isChangeOk = false;

	countStartFlag = false;
	respawnTimer = 0;
	respawnTimerLimit = 120;

	currentCoin = 0;
	elderCoin = 0;
}

void Map::Create(const bool init)
{
	if (init) Initialize();
	else Reset();
	stage++;

	// ノーマルステージ
	if (stage % 4 != 0)
	{
		int crystalPattern = 0;
		// クリスタル配置
		crystalPattern = rand() % 9;
		for (size_t i = 0; i < 3; i++)
		{
			Change(crystalPos[crystalPattern][i], CrystalBlock);
			drawer.CreateBright(crystalPos[crystalPattern][i]);
		}
		// コイン配置
		for (size_t i = 0; i < COIN_NUM; i++)
		{
			Vector2Int coinBlockPos;
			while (true)
			{
				coinBlockPos = { rand() % 10 ,rand() % 10 };
				if (GetMapState(coinBlockPos) == Block)
				{
					Change(coinBlockPos, CoinBlock);
					break;
				}
			}
		}
		// ボム配置
		int bombNum = stage / 4 + 1;
		for (size_t i = 0; i < 4; i++)
		{
			Vector2Int bombBlockPos;
			while (true)
			{
				bombBlockPos = { rand() % 10 ,rand() % 10 };
				if (GetMapState(bombBlockPos) == Block)
				{
					Change(bombBlockPos, BombBlock);
					int random = rand() % 4;
					drawer.CreateArrow(bombBlockPos, random);
					Bomb b;
					b.Initialize(bombBlockPos, random);
					bomb.push_back(b);
					break;
				}
			}
		}
	}
	else//　ボーナスステージ
	{
		//クリスタル配置
		for (size_t i = 0; i < 3; i++)
		{
			Change(bSC[i], CrystalBlock);
			drawer.CreateBright(bSC[i]);
		}

		//ボム配置
		for (size_t i = 0; i < 8; i++)
		{
			Change(bSB[i], BombBlock);
			Bomb b;
			if (i == 0 || i == 3 || i == 4)
			{
				drawer.CreateArrow(bSB[i], Right);
				b.Initialize(bSB[i], Right);
				bomb.push_back(b);
			}

			if (i == 1 || i == 2)
			{
				drawer.CreateArrow(bSB[i], Up);
				b.Initialize(bSB[i], Up);
				bomb.push_back(b);
			}

			if (i == 5 || i == 7)
			{
				drawer.CreateArrow(bSB[i], Left);
				b.Initialize(bSB[i], Left);
				bomb.push_back(b);
			}

			if (i == 6)
			{
				drawer.CreateArrow(bSB[i], Down);
				b.Initialize(bSB[i], Down);
				bomb.push_back(b);
			}
		}

		//コイン配置
		for (size_t i = 0; i < 26; i++)
		{
			Change(bSCG[i], CoinBlock);
			drawer.CreateBright(bSCG[i]);
		}

	}

	if (GetStage() % 4 == 0) currentCoin = BONUS_COIN_NUM - CountBlockNum(CoinBlock);
	else currentCoin = COIN_NUM - CountBlockNum(CoinBlock);
	elderCoin = currentCoin;
}

void Map::CreateTutorial()
{
	Reset();

	for (size_t i = 0; i < 5; i++)
	{
		if (i == 0 || i == 1 || i == 2)
		{
			//クリスタル
			Change(tB[i], CrystalBlock);
			drawer.CreateBright(tB[i]);
		}

		if (i == 3)
		{
			Change(tB[i], BombBlock);
			Bomb b;
			drawer.CreateArrow(tB[i], Up);
			b.Initialize(tB[i], Up);
			bomb.push_back(b);
		}

		if (i == 4)
		{
			Change(tB[i], CoinBlock);
			drawer.CreateBright(tB[i]);
		}

	}

}

void Map::NextStage()
{
	isNext = true;
}

void Map::Update()
{
	bbList.Update();
	Vector2Int n;
	bool b;
	for (size_t i = 0; i < 2; i++)
	{
		if (i) b = bbList.PopBroken(n);
		else b = bbList.PopExposure(n);

		if (b)
		{
			breakCount -= i;
			if (breakCount <= 0) breakCount = 0;
			drawer.ChipBreak(n);
			drawer.EraseArrowAndBright(n);
			Change(n, None);
			countStartFlag = true;
		}
	}
	RespawnTimerUpdate();

	Change(*playerPos, None);

	scoreCoin = CoinUpdate();
	crystalCounter = CrystalRemain();
	if (crystalCounter >= 3) NextStage();

	for (size_t i = 0; i < bomb.size(); i++)
	{
		bomb[i].Rotate();
	}
	drawer.Update();
	NextPreparation();
}

void Map::Change(Vector2Int num, BlockName blockName)
{
	assert(IsInsideValue(num.x, map.size()));
	assert(IsInsideValue(num.y, map.size()));
	drawer.EraseArrowAndBright(num);
	map[num.y][num.x] = blockName;
	drawer.ChipInit(num, blockName);
}

void Map::RespawnTimerUpdate()
{
	if (!countStartFlag) return;
	if (++respawnTimer < respawnTimerLimit) return;
	Respawn();
	drawer.EraseArrowAndBright(*playerPos);
	Change(*playerPos, None);
	respawnTimer = 0;
	countStartFlag = false;
}

int Map::CoinUpdate()
{
	int result = 0;
	if (GetStage() % 4 == 0) currentCoin = 26 - CountBlockNum(CoinBlock);
	else currentCoin = 7 - CountBlockNum(CoinBlock);

	if (currentCoin > elderCoin) result += (currentCoin - elderCoin);
	elderCoin = currentCoin;

	return result;
}

void Map::NextPreparation()
{
	if (!isNext) return;
	if (bbList.IsAct()) return;
	isChangeOk = true;
}

void Map::Respawn()
{
	for (size_t y = 0; y < map.size(); y++) 
	{
		for (size_t x = 0; x < map[y].size(); x++)
		{
			if (map[y][x] == None)
			{
				map[y][x] = Block;
				drawer.EraseArrowAndBright({ (int)x, (int)y });
				drawer.ChipInit({ (int)x, (int)y }, Block);
			}
		}
	}
}

void Map::BombDestroy(int bombIndex, Player* player)
{
	vector<Vector2Int>destroyPos = bomb[bombIndex].Explosion();

	for (size_t i = 0; i < destroyPos.size(); i++)
	{
		for (size_t j = 0; j < bomb.size(); j++)
		{
			if (destroyPos[i] == bomb[j].GetPos() && !bomb[j].IsExplosion())
			{
				bbList.PushBuck(destroyPos[i], true);
				EraseBomb(j);
				BombDestroy(j, player);
			}
		}
		if (destroyPos[i] == *playerPos) { player->DamageCountUp(); }
		bbList.PushBuck(destroyPos[i], true);
	}
}

void Map::EraseBomb(const int num)
{
	if (bomb.size() <= 0) return;
	if (bomb.size() >= num) return;
	bomb.erase(std::begin(bomb) + num);
}

void Map::Draw(const Vector2Int& camera)
{
	drawer.Draw(camera);
	bbList.DrawDebug();
}

size_t Map::CountBlockNum(BlockName blockName)
{
	size_t num = 0;
	for (size_t y = 0; y < map.size(); y++)
	{
		for (size_t x = 0; x < map[0].size(); x++)
		{
			num += map[y][x] == blockName;
		}
	}
	return num;
}