#pragma once
// 座標用変数
typedef struct Vector2
{
	float x, y;
}Vector2;

// 等速アニメーション描画に使う変数
// 基本的には picNum と timer の値だけ初期化すればいい。
typedef struct Anime
{
	int picNum;	// 画像の枚数
	int timer;	// 1枚の描画時間(フレーム)
	int nextTimer = timer;	// タイマー初期値の記録用
	int animeNum = 0;	// 現在の画像配列を記録するための変数
}Anime;