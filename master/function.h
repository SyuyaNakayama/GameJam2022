#pragma once
#include "Vector2.h"
// 最大値最小値を設定
void Clamp(int& num, int max, int min = 0);
void Clamp(float& num, float max, float min = 0);
void Clamp(Vector2Int& num, Vector2Int max, Vector2Int min = { 0,0 });

bool IsInsideValue(int num, int max, int min = 0);
// デバッグ用に使います(但しint型のみ)
void DrawDebugNumber(int num, int y = 0);
void DrawDebugNumber(float num, int y = 0);
void DrawBoxWithVectorInt(Vector2Int pos, Vector2Int rad, int color, bool fillFlag = 1);