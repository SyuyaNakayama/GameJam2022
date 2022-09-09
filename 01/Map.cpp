#include "Map.h"
#include "function.h"
#include <cassert>

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
	map[num.y][num.x] = blockName;
}

void Map::Respawn()
{
	for (size_t y = 0; y < map.size(); y++) {
		for (size_t x = 0; x < map[y].size(); x++)
		{
			if (map[y][x] == None)
			{
				map[y][x] = Block;
			}
		}
	}
}

void Map::Create()
{
	Init();
	crystalPattern = rand() % 9;
	for (size_t i = 0; i < 3; i++)
	{
		Change(crystalPos[crystalPattern][i], CrystalBlock);
	}
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