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
#include <string>
#include <fstream>
#include <algorithm>
#include "Ranking.h"
#include "UIDrawer.h"

using namespace std;

// ウィンドウのサイズ
const Vector2Int WIN_SIZE = { 1920,980 };

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
#pragma region 初期設定
	SetOutApplicationLogValidFlag(false);
	ChangeWindowMode(TRUE);
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);
	SetMainWindowText("之の人、採掘場にて。\n　～アレッヒの地下奴隷～");
	SetGraphMode(WIN_SIZE.x, WIN_SIZE.y, 32);
	SetWindowSizeExtendRate(1.0);
	SetDrawScreen(DX_SCREEN_BACK);
	if (DxLib_Init() == -1) { return -1; }
#pragma endregion
	// ---定数の宣言と初期化---
	Scene scene = Scene::Play;
	Color color;
	// ---変数の宣言と初期化---
	Font font;

	Input* input = Input::GetInstance();
	input->Load();

	int score = 0;
	int scoreCoin = 0;

	int currentCoin = 0;
	int elderCoin = 0;
	int crystalCounter = 0;

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

	UIDrawer ui;
	ui.LoadAndSet(player.GetActionCountPointer(), &scoreCoin, &crystalCounter);
	ui.Initialize();

	Timer timer = { GetNowCount() ,100 };
	Pad* pad = Pad::GetInstance();

	int fontSize = 48;

	RankingManager ranking;
	ranking.Reset(); // デバッグ用
	ranking.Load();
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

			if (map.GetStage() % 4 == 0) currentCoin = 26 - map.CountBlockNum(CoinBlock);
			else currentCoin = 7 - map.CountBlockNum(CoinBlock);

			if (currentCoin > elderCoin) scoreCoin += (currentCoin - elderCoin);
			elderCoin = currentCoin;

			crystalCounter = 3 - map.CountBlockNum(CrystalBlock);

			if (crystalCounter == 3)
			{
				map.NextStage();
				player.Reset({ rand() % 2 + 4,rand() % 2 + 4 }, Up);
				map.Change(player.GetPos(), None);
				timer = { GetNowCount() ,120 };
			}

			if (player.GetActionCount() <= 0 || timer.CountDown(player.GetDamageCount()))
			{
				score = (scoreCoin * 100) * (1 + (0.1 * map.GetStage())) + (map.GetBombBreakCount() * 50);
				scene = Result; SetFontSize(96); 
			}

			ui.Update();
			break;
		case Result:
			if (input->keys->IsTrigger(KEY_INPUT_SPACE))
			{
				scene = Ranking;
				ranking.Update(score);
			}
			break;
		case Ranking:
			if (input->keys->IsTrigger(KEY_INPUT_SPACE)) { scene = Title; }
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
			ui.Draw(camera.GetPos());
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
		case Ranking:
			DrawFormatStringToHandle(400, 100, color.White, font.Use(FontSize::LL), "スコア:%d", score);
			ranking.Draw(font);
			break;
		}

		ScreenFlip();
		// 20ミリ秒待機(疑似60FPS)
		WaitTimer(20);
#pragma endregion
	}
#pragma region 終了処理
	// 全リソースファイル削除
	InitGraph();
	InitSoundMem();
	InitFontToHandle();
	DxLib_End();
	return 0;
#pragma endregion
}