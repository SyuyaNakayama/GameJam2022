#include "DxLib.h"
#include "Vector2.h"
#include "Input.h"
#include "function.h"
#include "Map.h"
#include "Player.h"
#include "enum.h"
#include "Timer.h"
#include "Camera.h"
#include "Font.h"
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <string>

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
	SetMainWindowText("GameJam2022_コノヒト、サイクツジョウニテ。");
	SetGraphMode(WIN_SIZE.x, WIN_SIZE.y, 32);
	SetWindowSizeExtendRate(1.0);
	SetDrawScreen(DX_SCREEN_BACK);
	if (DxLib_Init() == -1) { return -1; }
	srand(time(0));
#pragma endregion
	// ---定数の宣言と初期化---
	Scene scene = Scene::Result;
	Color color;
	// ---変数の宣言と初期化---
	Font font;

	Input* input = Input::GetInstance();
	input->Load();

	int score = 0;
	int scoreCoin = 0;

	Camera camera;
	camera.Initialize({});

	Map map;
	map.LoadAndSet();
	map.Create();

	Player player;
	player.LoadAndSet(&map);
	player.Initialize({ rand() % 2 + 4,rand() % 2 + 4 }, Up);

	map.SetOutSide(&camera, player.GetPosAdress());
	map.Change(player.GetPos(), None);

	Timer timer = { GetNowCount() ,100 };
	Pad* pad = Pad::GetInstance();

	int fontSize = 48;
	vector<int> prologueFontColor(8, 0);
	vector<string> prologueString =
	{
		"時は制暦2173年、",
		"アレッヒでは1人の男が",
		"アクリスの人間から",
		"強制労働が強いられた。",
		"鉱石を見つければ",
		"それが給料になる。",
		"そんな男の地下採掘場でのお話。",
		"\nSPACEで次へ→"
	};
	SetFontSize(fontSize);
	while (!(ProcessMessage() == -1 || CheckHitKey(KEY_INPUT_ESCAPE)))
	{
#pragma region 更新処理
		ClearDrawScreen();

		input->Update();
		switch (scene)
		{
		case Title:
			if (input->keys->IsTrigger(KEY_INPUT_SPACE)) { scene = Prologue; }
			break;
		case Prologue:
			for (size_t i = 0; i < prologueFontColor.size(); i++)
			{
				const int INC_NUM = 4;
				if (i == 0) { prologueFontColor[i] += INC_NUM; }
				else { if (prologueFontColor[i - 1] >= 200) { prologueFontColor[i] += INC_NUM; } }
				Clamp(prologueFontColor[i], 255);
			}
			if (prologueFontColor.back() >= 150 && input->keys->IsTrigger(KEY_INPUT_SPACE)) { scene = Tutorial; }
			if (input->keys->IsTrigger(KEY_INPUT_S)) { scene = Tutorial; }
			break;
		case Tutorial:
			break;
		case Play:
			player.Update();
			if (input->keys->IsTrigger(KEY_INPUT_R))
			{
				map.Create();
				player.Reset({ rand() % 2 + 4,rand() % 2 + 4 }, Up);
				map.Change(player.GetPos(), None);
			}

			map.Update();
			if (map.CountBlockNum(CrystalBlock) == 0)
			{
				map.NextStage();
				scoreCoin += 7 - map.CountBlockNum(CoinBlock);
				player.Reset({ rand() % 2 + 4,rand() % 2 + 4 }, Up);
				map.Change(player.GetPos(), None);
				timer = { GetNowCount() ,120 };
			}

			if (player.GetActionCount() <= 0 || timer.CountDown(player.GetDamageCount())) { scene = Result; SetFontSize(96); }
			break;
		case Result:
			score = (scoreCoin * 100) * (1 + (0.1 * map.GetStage())) + (map.GetBombBreakCount() * 50);
			break;
		}
		camera.Update();
		pad->Update();
#pragma endregion
#pragma region 描画処理
		switch (scene)
		{
		case Title:
			font.DrawUseFont({ 80,150 }, color.White, "之の人、採掘場にて。\n　～アレッヒの地下奴隷～", FontSize::LL);
			font.DrawUseFont({ 370,450 }, color.White, "PRESS START", FontSize::LL);
			break;
		case Prologue:
			for (int i = 0; i < prologueFontColor.size(); i++)
			{
				font.DrawUseFont({ 200,200 + (font.GetFontSize(FontSize::L) + 5) * i },
					GetColor(prologueFontColor[i], prologueFontColor[i], prologueFontColor[i]),
					prologueString[i], FontSize::L);
			}
			font.DrawUseFont({ 1050,50 }, color.White, "S:Skip", FontSize::L);
			break;
		case Tutorial:
			break;
		case Play:
			map.Draw(camera.GetPos());
			player.Draw(camera.GetPos());
			timer.Draw({ 0,32 });
			DrawFormatString(0, 0, color.White, "コイン残り%d枚", map.CountBlockNum(CoinBlock));
			DrawFormatString(400, 0, color.White, "行動回数:%d回", player.GetActionCount());
			DrawFormatString(400, 50, color.White, "クリスタル:%d個", map.CountBlockNum(CrystalBlock));
			DrawFormatString(400, 96, color.White, "ボムによる破壊:%d個", map.GetBombBreakCount());
			DrawFormatString(800, 0, color.White, "ステージ:%d", map.GetStage());
			break;
		case Result:
			font.DrawUseFont({ 400,150 }, color.White, "リザルト", FontSize::LL);
			DrawFormatStringToHandle(400, 350, color.White, font.Use(FontSize::LL), "スコア:%d", score);
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