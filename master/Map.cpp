#include "Map.h"
#include "function.h"
#include <cassert>

void Map::BombDestroy(int bombIndex, Player* player)
{
	vector<Vector2Int>destroyPos = bomb[bombIndex].Explosion();

	for (size_t i = 0; i < destroyPos.size(); i++) {
		for (size_t j = 0; j < bomb.size(); j++)
		{
			if (destroyPos[i] == bomb[j].GetPos() && !bomb[j].IsExplosion())
			{
				BombDestroy(j, player);
			}
		}
		if (destroyPos[i] == player->GetLastSelectChip()) { player->DamageCountUp(); }
		drawer.ChipBreak(destroyPos[i]);
		drawer.EraseArrowAndBright(destroyPos[i]);
		Change(destroyPos[i], None);
	}
	for (size_t y = 0; y < map.size(); y++) {
		for (size_t x = 0; x < map[y].size(); x++)
		{
			if (map[y][x] == None)
			{
				bombBreak++;
			}
		}
	}
	bombBreak--;
}

void Map::Respawn()
{
	for (size_t y = 0; y < map.size(); y++) {
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
			drawer.ChipInit({ (int)x, (int)y }, Block);
		}
	}
	bomb.clear();
	drawer.ClearArrowAndBright();
}

void Map::Change(Vector2Int num, BlockName blockName)
{
	assert(IsInsideValue(num.x, map.size()));
	assert(IsInsideValue(num.y, map.size()));
	drawer.EraseArrowAndBright(num);
	map[num.y][num.x] = blockName;
	drawer.ChipInit(num, blockName);
}

void Map::Create()
{
	Init();
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
	for (size_t i = 0; i < 4; i++)
	{
		Vector2Int bombBlockPos;
		while (1)
		{
			bombBlockPos = { rand() % 10 ,rand() % 10 };
			if (GetMapState(bombBlockPos) == Block)
			{
				Change(bombBlockPos, BombBlock);
				int random = rand() % 4;
				drawer.CreateArrow(bombBlockPos, random);
				bomb.push_back({ bombBlockPos, random});
				break;
			}
		}
	}
}

void Map::Draw(const Vector2Int& camera)
{
	//Vector2Int boxPos{};
	//for (size_t y = 0; y < map.size(); y++) {
	//	for (size_t x = 0; x < map[y].size(); x++)
	//	{
	//		boxPos = pos + Vector2Int(2 * chipRad * x, 2 * chipRad * y);
	//		DrawBoxWithVectorInt(boxPos, { chipRad ,chipRad }, CHIP_COLOR[map[y][x]]);
	//		if (map[y][x] != BombBlock) { continue; }
	//		for (size_t i = 0; i < bomb.size(); i++)
	//		{
	//			if (!(bomb[i].GetPos().x == x && bomb[i].GetPos().y == y)) { continue; }
	//			Vector2Int pos = GetChipPos(bomb[i].GetPos());
	//			switch (bomb[i].GetDirection())
	//			{
	//			case Up:
	//				DrawLine(pos.x, pos.y, pos.x, pos.y - 32, color.Black);
	//				break;
	//			case Down:
	//				DrawLine(pos.x, pos.y, pos.x, pos.y + 32, color.Black);
	//				break;
	//			case Left:
	//				DrawLine(pos.x, pos.y, pos.x - 32, pos.y, color.Black);
	//				break;
	//			case Right:
	//				DrawLine(pos.x, pos.y, pos.x + 32, pos.y, color.Black);
	//				break;
	//			}
	//			break;
	//		}
	//	}
	//}
	drawer.Draw(camera);
}

void Map::LoadAndSet()
{
	drawer.Load();
	drawer.SetLeftTop(&pos);
}

void Map::SetOutSide(Camera* camera, Vector2Int* playerPos)
{
	drawer.SetCamera(camera);
	drawer.SetPlayerPos(playerPos);
}

void Map::Update()
{
	drawer.Update();
	for (size_t i = 0; i < bomb.size(); i++) { bomb[i].Rotate(); }
}

void Map::DrawChipInit(const Vector2Int& num, const int blockName)
{
	drawer.ChipInit(num, blockName);
}

void Map::DrawChipBreak(const Vector2Int& num)
{
	drawer.ChipBreak(num);
}

void Map::DrawArrowInit(const Vector2Int& num, const int direction)
{
	drawer.CreateArrow(num, direction);
}

void Map::DrawBrightInit(const Vector2Int& num)
{
	drawer.CreateBright(num);
}

void Map::DrawBright()
{
	drawer.ChipBright();
}

void Map::DrawErase(const Vector2Int& num)
{
	drawer.EraseArrow(num);
	drawer.EraseBright(num);
}

void Map::SetBrightness(const int brightness)
{
	drawer.SetBrightness(brightness);
}
