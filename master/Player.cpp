#include "Player.h"
#include "function.h"
#include "DxLib.h"
#include <math.h>

Player::Player(Vector2Int pos_, Map* pMap)
{
	selectPos = pos = pos_;
	mapPointer = pMap; rad = pMap->GetRadius();
	pad = Pad::GetInstance();
}

void Player::Move()
{
	input.Update();
	Vector2Int prePos = pos;
	Vector2Int preSelectPos = selectPos;

	switch (mode)
	{
	case Mode::Move:
		if (input.IsTrigger(KEY_INPUT_RIGHT)) { direction = Right; }
		if (input.IsTrigger(KEY_INPUT_LEFT)) { direction = Left; }
		if (input.IsTrigger(KEY_INPUT_UP)) { direction = Up; }
		if (input.IsTrigger(KEY_INPUT_DOWN)) { direction = Down; }
		break;
	case Select:
		if (input.IsTriggerMoveKey() && selectNum > 0)
		{
			bool isOk = 1;
			if (!selectChip.empty())
			{
				for (size_t i = 0; i < selectChip.size(); i++)
				{
					isOk &= !(selectPos == selectChip[i]);
				}
			}
			if (isOk)
			{
				selectChip.push_back(selectPos);
				if (mapPointer->GetMapState(selectPos) == BombBlock)
				{
					mode = Mode::Move;
				}
				selectNum--;
			}
		}
		selectPos.x += input.IsTrigger(KEY_INPUT_RIGHT) - input.IsTrigger(KEY_INPUT_LEFT);
		selectPos.y += input.IsTrigger(KEY_INPUT_DOWN) - input.IsTrigger(KEY_INPUT_UP);
		break;
	}

	Clamp(selectPos, mapPointer->GetMapSize() - Vector2Int(1, 1));
	if (mapPointer->GetMapState(selectPos) == None)
	{
		selectPos = preSelectPos;
	}
}

void Player::Destroy()
{
	if (mode == Mode::Move)
	{
		selectPos = pos;
		{
			switch (direction)
			{
			case Up:    selectPos.y--; break;
			case Down:  selectPos.y++; break;
			case Left:  selectPos.x--; break;
			case Right: selectPos.x++; break;
			}
		}
	}
	Clamp(selectPos, mapPointer->GetMapSize() - Vector2Int(1, 1));

	switch (mapPointer->GetMapState(selectPos))
	{
	case Block: case CoinBlock: case CrystalBlock: case BombBlock:
		if (!input.IsTrigger(KEY_INPUT_SPACE)) { break; }
		if (mode == Mode::Move) { mode = Select; }
		else if (mode == Select) { mode = Mode::Move; }
	}

	if (!selectChip.empty())
	{
		if (mapPointer->GetMapState(selectChip.back()) == BombBlock || input.IsTrigger(KEY_INPUT_SPACE))
		{
			if (mapPointer->GetMapState(selectChip.back()) == BombBlock)
			{
				// îöíeÇÃÉuÉçÉbÉNîjâ˙
				for (size_t i = 0; i < mapPointer->GetBomb().size(); i++)
				{
					if (mapPointer->GetBomb()[i].GetPos() == selectChip.back())
					{
						mapPointer->BombDestroy(i,this);
					}
				}
			}
			for (size_t i = 0; i < selectChip.size(); i++)
			{
				mapPointer->DrawChipBreak(selectChip[i]);
				mapPointer->Change(selectChip[i], None);
			}
			if (mode == Mode::Move) { pos = selectChip.back(); }
			selectNum = DESTROY_MAX;
			actionNum--;
			destroyAnimetionFlag = 1;
			countStartFlag = 1;
			selectChip.clear();
		}
	}

	if (input.IsTrigger(KEY_INPUT_C))
	{
		selectNum = DESTROY_MAX;
		mode = Mode::Move;
		selectChip.clear();
	}

	if (!countStartFlag) { return; }
	if (++respawnTimer < respawnTimerLimit) { return; }
	mapPointer->Respawn();
	mapPointer->Change(pos, None);
	respawnTimer = 0;
	countStartFlag = 0;
}

void Player::Draw()
{
	Color color;
	DrawCircle(mapPointer->GetChipPos(pos).x, mapPointer->GetChipPos(pos).y, 32, color.Cyan);
	for (size_t i = 0; i < selectChip.size(); i++)
	{
		if (mode == Mode::Select)
		{
			DrawBoxWithVectorInt(mapPointer->GetChipPos(selectChip[i]), Vector2Int(mapPointer->GetRadius(), mapPointer->GetRadius()), color.Magenta, 1);
		}
	}
	DrawDebugNumber(damageCount, 96);
	DrawBoxWithVectorInt(mapPointer->GetChipPos(selectPos), Vector2Int(mapPointer->GetRadius(), mapPointer->GetRadius()), color.Blue, mode);
}