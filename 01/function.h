#pragma once
#include "Vector2.h"
// ただの2乗の関数
int Square(int num);
// 数をループさせる関数
void NumberLoop(int& num, int max, int min = 0);
// 最大値最小値を設定
void Clamp(int& num, int max, int min = 0);
// デバッグ用に使います(但しint型のみ)
void DrawDebugNumber(int num, int y = 0);
void DrawBoxWithVectorInt(Vector2Int pos, Vector2Int rad, int color, bool fillFlag = 1);