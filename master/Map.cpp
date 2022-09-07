#include "Map.h"
#include "function.h"
#include <cassert>

Map::Map(Vector2Int num)
{
	SetMapSize(num);
}

void Map::SetMapSize(Vector2Int num)
{
	map.resize(num.y);
	for (size_t i = 0; i < map.size(); i++) { map[i].resize(num.x); }
}

Vector2Int Map::GetMapSize()
{
	assert(!map.empty());
	return { (int)map[0].size(),(int)map.size() };
}

void Map::MapInit()
{
	for (size_t y = 0; y < map.size(); y++) {
		for (size_t x = 0; x < map[y].size(); x++)
		{
			map[y][x] = None;
		}
	}
}

void Map::Change(Vector2Int num, BlockName blockName)
{
	map[num.y][num.x] = blockName;
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
