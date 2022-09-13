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
#include "SoundManeger.h"

using namespace std;

// ウィンドウのサイズ
const Vector2Int WIN_SIZE = { 1920,980 };

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
#pragma region 初期設定
	SetOutApplicationLogValidFlag(false);
	ChangeWindowMode(1);
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);
	SetMainWindowText("之の人、採掘場にて。\n　〜アレッヒの地下奴隷〜");
	SetGraphMode(WIN_SIZE.x, WIN_SIZE.y, 32);
	SetWindowSizeExtendRate(1.0);
	SetDrawScreen(DX_SCREEN_BACK);
	if (DxLib_Init() == -1) { return -1; }
#pragma endregion
	// 音
	SoundManeger sound;

	// ---定数の宣言と初期化---
	Scene scene = Scene::Play;
	Color color;
	// ---変数の宣言と初期化---
	Font font;

	Input* input = Input::GetInstance();
	input->Load();

	int score = 0;

	Camera camera;
	camera.Initialize({});

	Map map;
	map.LoadAndSet();
	map.Initialize();
	if (scene == Play) map.Create();
	if (scene == Tutorial) map.CreateTutorial();

	Player player;
	player.LoadAndSet(&map);
	player.Initialize({ rand() % 2 + 4,rand() % 2 + 4 }, Up);

	map.SetOutSide(&camera, player.GetPosAdress());
	map.Change(player.GetPos(), None);

	UIDrawer ui;
	ui.LoadAndSet(player.GetActionCountPointer(), &map.scoreCoin, &map.crystalCounter);
	ui.Initialize();

	Timer timer = { GetNowCount() ,100 };

	RankingManager ranking;
	ranking.Reset(); // ***** デバッグ用(提出時はコメントアウトすること！！！) ***** //
	ranking.Load();

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
	vector<int> prologueFontColor(prologueString.size(), 0);

	SetFontSize(48);

	while (!(ProcessMessage() == -1 || CheckHitKey(KEY_INPUT_ESCAPE)))
	{
#pragma region 更新処理
		ClearDrawScreen();

		input->Update();
		switch (scene)
		{
			// --- タイトル --- //
		case Title:
			sound.PlayBGM(0);
			if (input->keys->IsTrigger(KEY_INPUT_SPACE)) { scene = Prologue; sound.StopBGM(0); }
			break;

			// --- プロローグ --- //
		case Prologue:
			sound.PlayBGM(1);
			for (size_t i = 0; i < prologueFontColor.size(); i++)
			{
				const int INC_NUM = 4;
				if (i == 0) { prologueFontColor[i] += INC_NUM; }
				else if (prologueFontColor[i - 1] >= 200) { prologueFontColor[i] += INC_NUM; }
				Clamp(prologueFontColor[i], 255);
			}
			if (prologueFontColor.back() >= 150 && input->keys->IsTrigger(KEY_INPUT_SPACE) ||
				input->keys->IsTrigger(KEY_INPUT_S))
			{
				scene = Tutorial;
				map.CreateTutorial();
				player.Reset({ 4,4 }, Up);
				sound.StopBGM(1);
			}

			break;

			// --- チュートリアル --- //
		case Tutorial:
			sound.PlayBGM(2);

			player.Update();
			if (input->keys->IsTrigger(KEY_INPUT_R))
			{
				map.CreateTutorial();
				player.Reset({ 4,4 }, Up);
			}

			map.Update();

			if (map.IsChangeOk() || input->keys->IsTrigger(KEY_INPUT_S))
			{
				scene = Play;
				score = 0;
				map.Create(true);
				player.Reset({ rand() % 2 + 4, rand() % 2 + 4 }, Up);
				ui.Initialize();
				timer.Reset();
				sound.StopBGM(2);
			}

			break;

			// --- ゲーム --- //
		case Play:
			sound.PlayBGM(3);

			player.Update();
			if (input->keys->IsTrigger(KEY_INPUT_R))
			{
				map.Create();
				player.Reset({ rand() % 2 + 4,rand() % 2 + 4 }, Up);
			}

			map.Update();

			if (map.IsChangeOk())
			{
				map.Create();
				if (map.GetStage() % 4 == 0) player.Reset({ 4,4 }, Up);
				else player.Reset({ rand() % 2 + 4,rand() % 2 + 4 }, Up);
				ui.Initialize();
				timer.Reset();
			}

			if (player.GetActionCount() <= 0 || timer.CountDown(player.GetDamageCount()))
			{
				score = (map.scoreCoin * 100) * (1 + (0.1 * map.GetStage())) + (map.GetBombBreakCount() * 50);
				scene = Result;
				sound.StopBGM(3);
			}

			ui.Update();
			break;

			// --- リザルト --- //
		case Result:
			sound.PlayBGM(4);
			if (input->keys->IsTrigger(KEY_INPUT_SPACE))
			{
				scene = Ranking;
				ranking.Update(score);
			}
			break;

		case Ranking:
			if (input->keys->IsTrigger(KEY_INPUT_SPACE)) { scene = Title; sound.StopBGM(4); }
			break;
		}
		camera.Update();
#pragma endregion
#pragma region 描画処理
		switch (scene)
		{
		case Title:
			font.DrawUseFont({ 80,150 }, color.White, "之の人、採掘場にて。\n　〜アレッヒの地下奴隷〜", FontSize::LL);
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
			ui.Draw(camera.GetPos());
			map.Draw(camera.GetPos());
			player.Draw(camera.GetPos());
			font.DrawUseFont({ 750,50 }, color.White, "S：チュートリアルSkip", FontSize::L);
			break;

		case Play:
			ui.Draw(camera.GetPos());
			map.Draw(camera.GetPos());
			player.Draw(camera.GetPos());
			timer.Draw({ 0,32 });


			//デバッグ
			DrawFormatStringToHandle(0, 0, color.White, font.Use(FontSize::L), "コイン残り%d枚", map.CountBlockNum(CoinBlock));
			DrawFormatStringToHandle(400, 0, color.White, font.Use(FontSize::L), "行動回数:%d回", player.GetActionCount());
			DrawFormatStringToHandle(400, 50, color.White, font.Use(FontSize::L), "クリスタル:%d個", map.CountBlockNum(CrystalBlock));
			DrawFormatStringToHandle(400, 96, color.White, font.Use(FontSize::L), "ボムによる破壊:%d個", map.GetBombBreakCount());
			DrawFormatStringToHandle(800, 0, color.White, font.Use(FontSize::L), "ステージ:%d", map.GetStage());
			break;

		case Result:
		case Ranking:
			font.DrawUseFont({ 400,150 }, color.White, "リザルト", FontSize::LL);
			DrawFormatStringToHandle(400, 350, color.White, font.Use(FontSize::LL), "スコア:%d", score);

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