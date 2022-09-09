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
			if (destroyPos[i] == bomb[j].GetPos() && !bomb[j].IsExplosion())
			{
				BombDestroy(j);
			}
		}
		Change(destroyPos[i], None);
	}
}

void Map::Respawn()
{
	for (size_t y = 0; y < map.size(); y++) {
		for (size_t x = 0; x < map[y].size(); x++)
		{
			if (map[y][x] == None) { map[y][x] = Block; }
		}
	}
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
	for (size_t i = 0; i < 12; i++)
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
}

void Map::Draw()
{
	Vector2Int boxPos{};
	for (size_t y = 0; y < map.size(); y++) {
		for (size_t x = 0; x < map[y].size(); x++)
		{
			boxPos = pos + Vector2Int(2 * chipRad * x, 2 * chipRad * y);
			DrawBoxWithVectorInt(boxPos, { chipRad ,chipRad }, CHIP_COLOR[map[y][x]]);
			if (map[y][x] == BombBlock)
			{
				for (size_t i = 0; i < bomb.size(); i++)
				{
					if (bomb[i].GetPos().x == x && bomb[i].GetPos().y == y)
					{
						Vector2Int pos = GetChipPos(bomb[i].GetPos());
						switch (bomb[i].GetDirection())
						{
						case Up:
							DrawLine(pos.x, pos.y, pos.x, pos.y - 32, color.Black);
							break;
						case Down:
							DrawLine(pos.x, pos.y, pos.x, pos.y + 32, color.Black);
							break;
						case Left:
							DrawLine(pos.x, pos.y, pos.x - 32, pos.y, color.Black);
							break;
						case Right:
							DrawLine(pos.x, pos.y, pos.x + 32, pos.y, color.Black);
							break;
						}
						break;
					}
				}
			}
		}
	}
}
