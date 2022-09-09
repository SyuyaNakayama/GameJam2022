#include "Map.h"
#include "function.h"
#include <cassert>

void Map::BombDestroy(int bombIndex)
{
	vector<Vector2Int>destroyPos = bomb[bombIndex].Explosion();

	for (size_t i = 0; i < destroyPos.size(); i++)
	{
		for (size_t j = 0; j < bomb.size(); j++)
		{
			if (destroyPos[i] == bomb[bombIndex].GetPos())
			{
				BombDestroy(j);
			}
		}
		Change(destroyPos[i], None);
	}
}

Vector2Int Map::GetMapSize()
{
	return { (int)map[0].size(),(int)map.size() };
}

BlockName Map::GetMapState(Vector2Int pos)
{
	return map[pos.y][pos.x];
}

size_t Map::CountBlockNum(BlockName blockName)
{
	size_t num = 0;
	for (size_t y = 0; y < map.size(); y++) {
		for (size_t x = 0; x < map[0].size(); x++)
		{
			num += map[y][x] == blockName;
		}
	}
	return num;
}

void Map::Init()
{
	for (size_t y = 0; y < map.size(); y++) {
		for (size_t x = 0; x < map[y].size(); x++)
		{
			map[y][x] = Block;
		}
	}
}

void Map::Change(Vector2Int num, BlockName blockName)
{
	assert(IsInsideValue(num.x, map.size()));
	assert(IsInsideValue(num.y, map.size()));
	map[num.y][num.x] = blockName;
}

void Map::Create()
{
	Init();
	// クリスタル配置
	crystalPattern = rand() % 9;
	for (size_t i = 0; i < 3; i++)
	{
		Change(crystalPos[crystalPattern][i], CrystalBlock);
	}
	// コイン配置
	for (size_t i = 0; i < COIN_NUM; i++)
	{
		Vector2Int coinBlockPos;
		while (1)
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
	for (size_t i = 0; i < 7; i++)
	{
		Vector2Int bombBlockPos;
		while (1)
		{
			bombBlockPos = { rand() % 10 ,rand() % 10 };
			if (GetMapState(bombBlockPos) == Block)
			{
				Change(bombBlockPos, BombBlock);
				bomb.push_back({ bombBlockPos,rand() % 4 });
				break;
			}
		}
	}
	//bomb.push_back({ {5,4},Right });
	//bomb.push_back({ {7,3},Up });
	//list<Bomb>::iterator bItr = bomb.begin();
	//Change(bItr->GetPos(), BombBlock);
	//bItr++;
	//Change(bItr->GetPos(), BombBlock);
}

void Map::Draw()
{
	Vector2Int boxPos{};
	for (size_t y = 0; y < map.size(); y++) {
		for (size_t x = 0; x < map[y].size(); x++)
		{
			boxPos = pos + Vector2Int(2 * chipRad * x, 2 * chipRad * y);
			DrawBoxWithVectorInt(boxPos, { chipRad ,chipRad }, CHIP_COLOR[map[y][x]]);
		}
	}
}
