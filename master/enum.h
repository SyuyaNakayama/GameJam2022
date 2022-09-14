#pragma once
#include "DxLib.h"
#include "Vector2.h"

enum BlockName { None, Block, CoinBlock, CrystalBlock, BombBlock };
enum Direction { Up, Down, Left, Right };
enum Mode { Select, Destroy, Move, Stop };
enum Scene { Title, Prologue, Tutorial, Play, Result, Ranking };

struct Color
{
	const int
		Black = GetColor(0, 0, 0),
		White = GetColor(255, 255, 255),
		Cyan = GetColor(0, 255, 255);
};