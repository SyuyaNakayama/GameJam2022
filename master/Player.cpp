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
		pos.x += input.isTrigger(KEY_INPUT_RIGHT) - input.isTrigger(KEY_INPUT_LEFT);
		pos.y += input.isTrigger(KEY_INPUT_DOWN) - input.isTrigger(KEY_INPUT_UP);

		if (input.isTrigger(KEY_INPUT_RIGHT)) { direction = Right; }
		if (input.isTrigger(KEY_INPUT_LEFT)) { direction = Left; }
		if (input.isTrigger(KEY_INPUT_UP)) { direction = Up; }
		if (input.isTrigger(KEY_INPUT_DOWN)) { direction = Down; }
		break;
	case Select:
		selectPos.x += input.isTrigger(KEY_INPUT_RIGHT) - input.isTrigger(KEY_INPUT_LEFT);
		selectPos.y += input.isTrigger(KEY_INPUT_DOWN) - input.isTrigger(KEY_INPUT_UP);
		break;
	}

	Clamp(pos.x, mapPointer->GetMapSize().x - 1);
	Clamp(pos.y, mapPointer->GetMapSize().y - 1);

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
		if (input.isTrigger(KEY_INPUT_SPACE))
		{
			if (mode == Mode::Move) { mode = Select; }
			else if (mode == Select) { mode = Mode::Move; }
		}
	}
}

void Player::Draw()
{
	Color color;
	int selectColor[] = { color.Blue,color.Yellow };
	DrawCircle(mapPointer->GetChipPos(pos).x, mapPointer->GetChipPos(pos).y, 32, GetColor(0, 255, 0));
	DrawBoxWithVectorInt(mapPointer->GetChipPos(selectPos), Vector2Int(mapPointer->GetRadius(), mapPointer->GetRadius()), color.Blue, mode);
}