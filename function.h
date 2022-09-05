#pragma once



// キー情報を得る
void GetKeyState(char* keys, char* oldkeys)
{
	if (keys == nullptr || oldkeys == nullptr)
	{
		return;
	}

	for (int i = 0; i < 256; ++i) oldkeys[i] = keys[i];
	GetHitKeyStateAll(keys);
}

// 連番出力で一列に画像が並んでいる時用のリソース読み込み関数
void LoadDivGraphLine(const TCHAR* fileName, int xNum, int xSize, int ySize, int* handleArray)
{
	if (fileName == nullptr || handleArray == nullptr)
	{
		return;
	}

	LoadDivGraph(fileName, xNum, xNum, 1, xSize, ySize, handleArray);
}

// ただの2乗の関数
int Square(int num)
{
	return num * num;
}

// デバッグ用に使います(但しint型のみ)
void DrawDebugNumber(int num, int y = 0)
{
	DrawFormatString(0, y, WHITE, "%d", num);
}

// Anime型変数に代入して使って下さい。
Anime DrawAnimation(Anime anime, int handleArray[], Vector2 center, Vector2 objRadius)
{
	anime = UpdateAnime(anime);
	DrawExtendGraph(center.x - objRadius.x, center.y - objRadius.y,
		center.x + objRadius.x, center.y + objRadius.y,
		handleArray[anime.animeNum], 1);
	return anime;
}

// キーを押した瞬間trueになる
bool PushButtion(int Buttion, char* keys, char* oldkeys)
{
	if (keys == nullptr || oldkeys == nullptr)
	{
		return false;
	}

	if (!oldkeys[Buttion] && keys[Buttion])
	{
		return true;
	}
	return false;
}