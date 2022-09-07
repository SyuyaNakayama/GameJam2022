#include "Player.h"
#include "function.h"
#include "DxLib.h"
#include <math.h>

Player::Player(Vector2Int pos_, int rad_)
{
	pos = pos_;	rad = rad_;
}

void Player::Move(Map& map)
{
	input.Update();
	pad.Update();

	Vector2Int prePos = pos;

	pos.x += input.isTrigger(KEY_INPUT_RIGHT) - input.isTrigger(KEY_INPUT_LEFT);
	pos.y += input.isTrigger(KEY_INPUT_DOWN) - input.isTrigger(KEY_INPUT_UP);
	pos.x += pad.Right() - pad.Left();
	pos.y += pad.Down() - pad.Up();

	Clamp(pos.x, map.GetMapSize().x - 1);
	Clamp(pos.y, map.GetMapSize().y - 1);

	if (map.GetMapState(pos) != None) { pos = prePos; }
}

void Player::Draw(Map& map)
{
	DrawCircle(map.GetChipPos(pos).x, map.GetChipPos(pos).y, 32, GetColor(0, 255, 0));
}