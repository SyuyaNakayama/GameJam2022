#include "Player.h"
#include "function.h"
#include "DxLib.h"
#include <math.h>

Player::Player(Vector2Int pos_, int rad_, Map* pMap)
{
	selectPos = pos = pos_;
	rad = rad_; mapPointer = pMap;
}

void Player::Move()
{
	input.Update();
	Vector2Int prePos = pos;
	Vector2Int preSelectPos = selectPos;

	switch (mode)
	{
	case Mode::Move:
		pos.x += input.IsTrigger(KEY_INPUT_RIGHT) - input.IsTrigger(KEY_INPUT_LEFT);
		pos.y += input.IsTrigger(KEY_INPUT_DOWN) - input.IsTrigger(KEY_INPUT_UP);

		if (input.IsTrigger(KEY_INPUT_RIGHT)) { direction = Right; }
		if (input.IsTrigger(KEY_INPUT_LEFT)) { direction = Left; }
		if (input.IsTrigger(KEY_INPUT_UP)) { direction = Up; }
		if (input.IsTrigger(KEY_INPUT_DOWN)) { direction = Down; }
		break;
	case Select:
		if (input.IsTriggerMoveKey() && selectNum > 0)
		{
			selectChip.push_back(selectPos);
			selectNum--;
		}
		selectPos.x += input.IsTrigger(KEY_INPUT_RIGHT) - input.IsTrigger(KEY_INPUT_LEFT);
		selectPos.y += input.IsTrigger(KEY_INPUT_DOWN) - input.IsTrigger(KEY_INPUT_UP);
		break;
	}

	Clamp(pos, mapPointer->GetMapSize() - Vector2Int(1, 1));
	Clamp(selectPos, mapPointer->GetMapSize() - Vector2Int(1, 1));

	switch (mapPointer->GetMapState(pos))
	{
	case Block:case CoinBlock:case CrystalBlock:
		pos = prePos;
	}
	switch (mapPointer->GetMapState(selectPos))
	{
	case None:
		selectPos = preSelectPos;
	}
}

void Player::Destroy()
{
	if (mode == Mode::Move) {
		selectPos = pos;
		switch (direction)
		{
		case Up:    selectPos.y--; break;
		case Down:  selectPos.y++; break;
		case Left:  selectPos.x--; break;
		case Right: selectPos.x++; break;
		}
	}

	switch (mapPointer->GetMapState(selectPos))
	{
	case Block:case CoinBlock:case CrystalBlock:
		if (input.IsTrigger(KEY_INPUT_SPACE))
		{
			if (mode == Mode::Move) { mode = Select; }
			else if (mode == Select) { mode = Mode::Move; }
		}
	}

	if (input.IsTrigger(KEY_INPUT_SPACE))
	{
		for (size_t i = 0; i < selectChip.size(); i++)
		{
			mapPointer->Change(selectChip[i], None);
		}
		selectChip.clear();
		selectNum = DESTROY_MAX;
	}
}

void Player::Draw()
{
	Color color;
	DrawCircle(mapPointer->GetChipPos(pos).x, mapPointer->GetChipPos(pos).y, 32, GetColor(0, 255, 0));
	DrawBoxWithVectorInt(mapPointer->GetChipPos(selectPos), Vector2Int(mapPointer->GetRadius(), mapPointer->GetRadius()), color.Blue, mode);
	for (size_t i = 0; i < selectChip.size(); i++)
	{
		if (mode == Mode::Select)
		{
			DrawBoxWithVectorInt(mapPointer->GetChipPos(selectChip[i]), Vector2Int(mapPointer->GetRadius(), mapPointer->GetRadius()), color.Yellow, 1);
		}
	}
}