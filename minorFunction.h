#pragma once
// 使用頻度が低い関数

// 数をループさせる関数
int NumberLoop(int num, int max, int min = 0)
{
	if (num >= max)num = min;
	if (num < min)num = max - 1;
	return num;
}

// アニメーション更新関数
Anime UpdateAnime(Anime anime)
{
	anime.timer--;
	anime.timer = NumberLoop(anime.timer, anime.nextTimer);

	if (anime.timer == 0)anime.animeNum++;

	anime.animeNum = NumberLoop(anime.animeNum, anime.picNum);

	return anime;
}