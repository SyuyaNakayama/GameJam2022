#include "DxLib.h"
#include "Vector2.h"
#include "Input.h"
#include "function.h"
#include "Map.h"
#include "Player.h"
#include "enum.h"
#include "Timer.h"
#include "Camera.h"
#include <vector>
#include <stdlib.h>
#include <time.h>

using namespace std;

// ウィンドウのサイズ
const Vector2Int WIN_SIZE = { 1280,1280 * 2 / 3 };

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
#pragma region 初期設定
	SetOutApplicationLogValidFlag(false);
	ChangeWindowMode(TRUE);
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);
	SetMainWindowText("GameJam2022_之の人、採掘場にて。～アレッヒの地下奴隷～");
	SetGraphMode(WIN_SIZE.x, WIN_SIZE.y, 32);
	SetWindowSizeExtendRate(1.0);
	SetDrawScreen(DX_SCREEN_BACK);
	if (DxLib_Init() == -1) { return -1; }
	srand(time(0));
#pragma endregion
	// ---定数の宣言と初期化---
	Scene scene = Scene::Play;
	Color color;
	// ---変数の宣言と初期化---
	int stage = 0, score = 0;
	Camera camera;
	camera.Initialize({});
	Map map;
	map.Create();
	Player player = { {rand() % 2 + 4,rand() % 2 + 4},&map };
	map.Change(player.GetPos(), None);
	map.DrawChipInit(player.GetPos(), None);
	map.SetOutSide(&camera, player.GetPosAdress());
	Timer timer = { GetNowCount() ,120 };
	Input input;
	Pad* pad = Pad::GetInstance();

	SetFontSize(32);
	while (!(ProcessMessage() == -1 || CheckHitKey(KEY_INPUT_ESCAPE)))
	{
#pragma region 更新処理
		ClearDrawScreen();

		switch (scene)
		{
		case Title:
			if (input.IsTrigger(KEY_INPUT_SPACE)) { scene = Tutorial; }
			break;
		case Tutorial:
			break;
		case Play:
			input.Update();
			player.Move();
			player.Destroy();
			if (input.IsTrigger(KEY_INPUT_R))
			{
				map.Create();
				player.SetPos({ rand() % 2 + 4,rand() % 2 + 4 });
				map.Change(player.GetPos(), None);
			}
			map.Update();
			if (player.GetActionCount() <= 0 || timer.CountDown(player.GetDamageCount())) { scene = GameOver; SetFontSize(96); }
			break;
		case GameOver:
			break;
		}
		camera.Update();
		pad->Update();
#pragma endregion
#pragma region 描画処理
		switch (scene)
		{
		case Title:
			DrawString(50, 150, "之の人、採掘場にて。\n\n　～アレッヒの地下奴隷～", color.White);
			break;
		case Tutorial:
			break;
		case Play:
			map.Draw(camera.GetPos());
			player.Draw();
			timer.Draw({ 0,32 });
			DrawFormatString(0, 0, color.White, "コイン残り%d枚", map.CountBlockNum(CoinBlock));
			DrawFormatString(400, 0, color.White, "行動回数:%d回", player.GetActionCount());
			break;
		case GameOver:
			DrawString(50, 150, "夏空へ、ゲームオーバー", color.White);
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