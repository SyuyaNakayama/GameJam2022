#include "Player.h"
#include "function.h"
#include "DxLib.h"
#include <math.h>

Player::Player(Vector2 pos_, int rad_)
{
	pos = pos_;	rad = rad_;
}

void Player::Move(Vector2Int moveLimitLeftUp,Vector2Int moveRightDown)
{
	input.UpdateKeyState();
	angle += (input.isInput(KEY_INPUT_RIGHT) - input.isInput(KEY_INPUT_LEFT)) * ROT_SPD;
	pos += Vector2(-sinf(angle), cosf(angle)) * ((input.isInput(KEY_INPUT_DOWN) - input.isInput(KEY_INPUT_UP)) * MOVE_SPD);
	Clamp(pos.x, moveRightDown.x, moveLimitLeftUp.x);
	Clamp(pos.y, moveRightDown.y, moveLimitLeftUp.y);
}

void Player::Draw()
{
	DrawCircle(pos.x, pos.y, 32, GetColor(0,255,0));
	DrawLine(pos.x, pos.y, pos.x + sinf(angle) * 30, pos.y - cosf(angle) * 30, GetColor(255, 0, 0));
}