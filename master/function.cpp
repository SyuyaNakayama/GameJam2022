#include "DxLib.h"
#include "function.h"
void Clamp(int& num, int max, int min)
{
	if (num > max) { num = max; }
	if (num < min) { num = min; }
}
void Clamp(float& num, float max, float min)
{
	if (num > max) { num = max; }
	if (num < min) { num = min; }
}
void Clamp(Vector2Int& num, Vector2Int max, Vector2Int min)
{
	if (num.x > max.x) { num.x = max.x; }
	if (num.x < min.x) { num.x = min.x; }
	if (num.y > max.y) { num.y = max.y; }
	if (num.y < min.y) { num.y = min.y; }
}

bool IsInsideValue(int num, int max, int min)
{
	return num <= max && num >= min;
}

void DrawDebugNumber(int num, int y)
{
	DrawFormatString(0, y, GetColor(255, 255, 255), "%d", num);
}
void DrawDebugNumber(float num, int y)
{
	DrawFormatString(0, y, GetColor(255, 255, 255), "%f", num);
}

void DrawBoxWithVectorInt(Vector2Int pos, Vector2Int rad, int color, bool fillFlag)
{
	Vector2Int
		pos1 = pos - rad,
		pos2 = pos + rad;

	DrawBox(pos1.x, pos1.y, pos2.x, pos2.y, color, fillFlag);
}