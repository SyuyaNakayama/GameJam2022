#pragma once
#include "DxLib.h"

enum BlockName { None, Block, CoinBlock, CrystalBlock, BombBlock };
enum Direction { Up, Down, Left, Right };
enum Mode { Select, Destroy, Move };
enum Scene { Title, Prologue, Tutorial, Play, Result, Ranking };

struct Color
{
	const int
		Black = GetColor(0, 0, 0),
		White = GetColor(255, 255, 255),
		Red = GetColor(255, 0, 0),
		Green = GetColor(0, 255, 0),
		Blue = GetColor(0, 0, 255),
		Yellow = GetColor(255, 255, 0),
		Cyan = GetColor(0, 255, 255),
		Magenta = GetColor(255, 0, 255);
};