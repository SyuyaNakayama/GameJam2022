#include "DxLib.h"
#include "numbering.h"
#include "function.h"

void GetKeyState()
{
	for (int i = 0; i < 256; ++i) oldkeys[i] = keys[i];
	GetHitKeyStateAll(keys);
}

// 連番出力で一列に画像が並んでいる時用のリソース読み込み関数
void LoadDivGraphLine(const TCHAR* fileName, int xNum, int xSize, int ySize, int* handleArray)
{
	LoadDivGraph(fileName, xNum, xNum, 1, xSize, ySize, handleArray);
}

// 数をループさせる関数
int NumberLoop(int num, int max, int min)
{
	if (num >= max)num = min;
	if (num < min)num = max - 1;
	return num;
}

// ただの2乗の関数
int Square(int num)
{
	return num * num;
}

// デバッグ用に使います(但しint型のみ)
void DrawDebugNumber(int num, int y)
{
	DrawFormatString(0, y, WHITE, "%d", num);
}

// 使うことはない関数です
Anime UpdateAnime(Anime anime)
{
	anime.timer--;
	anime.timer = NumberLoop(anime.timer, anime.nextTimer);

	if (anime.timer == 0)anime.animeNum++;

	anime.animeNum = NumberLoop(anime.animeNum, anime.picNum);

	return anime;
}

// Anime型変数に代入して使って下さい。
Anime DrawAnimation(Anime anime, int handleArray[], int x1, int y1, int x2, int y2)
{
	anime = UpdateAnime(anime);
	DrawExtendGraph(x1, y1, x2, y2, handleArray[anime.animeNum], 1);
	return anime;
}
Anime DrawAnimation(Anime anime, int handleArray[], Screen center, Screen objRadius)
{
	anime = UpdateAnime(anime);
	DrawExtendGraph(center.x, center.y, objRadius.x, objRadius.y, handleArray[anime.animeNum], 1);
	return anime;
}

bool PushButtion(int Buttion)
{
	if (!oldkeys[Buttion] && keys[Buttion])
	{
		return true;
	}
	return false;
}