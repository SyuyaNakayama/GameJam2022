#include "DxLib.h"
#include "Vector2.h"
#include "Input.h"
#include "function.h"
#include "Map.h"
#include "Player.h"
#include <vector>
#include <stdlib.h>
#include <time.h>

using namespace std;

// ウィンドウのサイズ
const Vector2Int WIN_SIZE = { 1280,1280 * 2 / 3 };

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
#pragma region DXlib初期設定
	SetOutApplicationLogValidFlag(false);
	ChangeWindowMode(TRUE);
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);
	SetMainWindowText("GameJam2022_之の人、採掘場にて。〜アレッヒの地下奴隷〜");
	SetGraphMode(WIN_SIZE.x, WIN_SIZE.y, 32);
	SetWindowSizeExtendRate(1.0);
	SetDrawScreen(DX_SCREEN_BACK);
	if (DxLib_Init() == -1) { return -1; }
	srand(time(0));
#pragma endregion
	// ---定数の宣言と初期化---
	enum Scene { Title, Tutorial, Play, GameOver };
	Scene scene = Scene::Title;

	const vector<Vector2Int>MAP_SIZE =
	{
		{9,9},
		{9,9},
		{9,9},
		{9,9}
	};

	const int STAGE_NUM = MAP_SIZE.size();

	Color color;
	// ---変数の宣言と初期化---
	Player player = { {700,600},32 };

	Map map = Vector2Int(9, 9);
	map.Change({ 0,2 }, BlockName::Block);

	SetFontSize(96);

	while (!(ProcessMessage() == -1 || CheckHitKey(KEY_INPUT_ESCAPE)))
	{
#pragma region 更新処理
		ClearDrawScreen();

		switch (scene)
		{
		case Title:
			break;
		case Tutorial:
			break;
		case Play:
			player.Move(map.GetMapPos(), {
					map.GetMapPos().x + 2 * map.GetRadius() * (map.GetMapSize().x - 1),
					map.GetMapPos().y + 2 * map.GetRadius() * (map.GetMapSize().y - 1) });
			break;
		case GameOver:
			break;
		default:
			break;
		}

#pragma endregion
#pragma region 描画処理
		switch (scene)
		{
		case Title:
			DrawString(50, 150, "之の人、採掘場にて。\n\n　〜アレッヒの地下奴隷〜", color.White);
			break;
		case Tutorial:
			break;
		case Play:
			map.Draw(map.GetPlayerMapChip(player), player.GetAngle());
			player.Draw();
			break;
		case GameOver:
			break;
		default:
			break;
		}

		ScreenFlip();
#pragma endregion
	}
#pragma region 終了処理
	// 全リソースファイル削除
	InitGraph();
	InitSoundMem();
	DxLib_End();
	return 0;
#pragma endregion
}