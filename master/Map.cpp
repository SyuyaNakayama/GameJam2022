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

Vector2Int Map::GetPlayerMapChip(Player player)
{
	Vector2Int plaPosInt = { (int)player.GetPos().x,(int)player.GetPos().y };
	plaPosInt -= pos - Vector2Int(mapChipRad, mapChipRad);
	return plaPosInt / mapChipRad / 2;
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

void Map::Draw(Vector2Int playerPos)
{
	for (size_t y = 0; y < map.size(); y++) {
		for (size_t x = 0; x < map[y].size(); x++)
		{
			Vector2Int boxPos = pos + Vector2Int(2 * mapChipRad * x, 2 * mapChipRad * y);
			DrawBoxWithVectorInt(boxPos, { mapChipRad ,mapChipRad }, CHIP_COLOR[map[y][x]]);
			if (playerPos.x == x && playerPos.y == y)
			{
				DrawBoxWithVectorInt(boxPos, { mapChipRad ,mapChipRad }, color.Red, 0);
			}
		}
	}
}
