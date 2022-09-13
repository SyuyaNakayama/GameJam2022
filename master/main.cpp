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
#include "SoundManager.h"
#include "SceneManager.h"

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
	SetMainWindowText("之の人、採掘場にて。\n　～アレッヒの地下奴隷～");
	SetGraphMode(WIN_SIZE.x, WIN_SIZE.y, 32);
	SetWindowSizeExtendRate(1.0);
	SetDrawScreen(DX_SCREEN_BACK);
	if (DxLib_Init() == -1) { return -1; }
#pragma endregion
	// 音
	SoundManager* sound = SoundManager::GetInstance();
	sound->Load();

	// シーン
	SceneManager scene;
	scene.Initialze(Scene::Title, WIN_SIZE);

	// ---定数の宣言と初期化---

	Color color;
	// ---変数の宣言と初期化---
	Font* font = Font::GetInstance();
	font->Load();

	Input* input = Input::GetInstance();
	input->Load();

	int score = 0;

	Camera camera;
	camera.Initialize({});

	Map map;
	map.LoadAndSet();
	map.Initialize();
	if (scene.GetScene() == Play) map.Create();
	if (scene.GetScene() == Tutorial) map.CreateTutorial();

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
		switch (scene.GetScene())
		{
			// --- タイトル --- //
		case Title:
			sound->PlayBGM(0);
			if (input->IsSelect()) scene.Change(Prologue);
			if (scene.IsChanged()) sound->StopBGM(0);
			break;

			// --- プロローグ --- //
		case Prologue:
			sound->PlayBGM(1);

			if (!scene.IsProcessing())
			{
				for (size_t i = 0; i < prologueFontColor.size(); i++)
				{
					const int INC_NUM = 4;
					if (i == 0) { prologueFontColor[i] += INC_NUM; }
					else if (prologueFontColor[i - 1] >= 200) { prologueFontColor[i] += INC_NUM; }
					Clamp(prologueFontColor[i], 255);
				}

				bool next = prologueFontColor.back() >= 150 && input->IsSelect() || input->keys->IsTrigger(KEY_INPUT_S);
				if (next) scene.Change(Tutorial);
			}

			if (scene.IsChanged())
			{
				score = 0;
				map.CreateTutorial();
				player.Reset({ 4,4 }, Up);
				sound->StopBGM(1);
			}
			break;

			// --- チュートリアル --- //
		case Tutorial:
			sound->PlayBGM(2);

			player.Update();
			if (input->keys->IsTrigger(KEY_INPUT_R))
			{
				map.CreateTutorial();
				player.Reset({ 4,4 }, Up);
			}

			map.Update();

			if (map.IsChange() || input->keys->IsTrigger(KEY_INPUT_S)) scene.Change(Play);
			if (scene.IsChanged())
			{
				score = 0;
				map.Create(true);
				player.Reset({ rand() % 2 + 4, rand() % 2 + 4 }, Up);
				ui.Initialize();
				timer.Reset();
				sound->StopBGM(2);
			}

			break;

			// --- ゲーム --- //
		case Play:
			sound->PlayBGM(3);

			player.Update();
			map.Update();

			if (map.IsChange())
			{
				map.Create();
				if (map.GetStage() % 4 == 0) player.Reset({ 4,4 }, Up);
				else player.Reset({ rand() % 2 + 4,rand() % 2 + 4 }, Up);
				ui.Initialize();
				timer.Reset();
			}

			if (input->keys->IsTrigger(KEY_INPUT_R))
			{
				map.Create();
				player.Reset({ rand() % 2 + 4,rand() % 2 + 4 }, Up);
				ui.Initialize();
				timer.Reset();
			}

			if (player.GetActionCount() <= 0 || timer.CountDown(player.GetDamageCount())) scene.Change(Result);
			if (scene.IsChanged())
			{
				score = (map.scoreCoin * 100) * (1 + (0.1 * map.GetStage())) + (map.GetBombBreakCount() * 50);
				ui.Initialize();
				timer.Reset();
				sound->StopBGM(3);
			}

			ui.Update();
			break;

			// --- リザルト --- //
		case Result:
			sound->PlayBGM(4);
			if (input->IsSelect())
			{
				scene.SetScene(Ranking);
				ranking.Update(score);
			}
			break;

		case Ranking:
			if (input->IsSelect()) scene.Change(Title);
			if (scene.IsChanged()) sound->StopBGM(4);
			break;
		}
		camera.Update();
		scene.Update();
#pragma endregion
#pragma region 描画処理
		switch (scene.GetScene())
		{
		case Title:
			font->DrawUseFont({ 80,150 }, color.White, "之の人、採掘場にて。\n　～アレッヒの地下奴隷～", FontSize::LL);
			font->DrawUseFont({ 370,450 }, color.White, "PRESS START", FontSize::LL);
			break;

		case Prologue:
			for (int i = 0; i < prologueFontColor.size(); i++)
			{
				font->DrawUseFont({ 200,200 + (font->GetFontSize(FontSize::L) + 5) * i },
					GetColor(prologueFontColor[i], prologueFontColor[i], prologueFontColor[i]),
					prologueString[i], FontSize::L);
			}
			font->DrawUseFont({ 1350,40 }, color.White, "S：Skip", FontSize::L);
			break;

		case Tutorial:
			ui.Draw(camera.GetPos());
			map.Draw(camera.GetPos());
			player.Draw(camera.GetPos());
			font->DrawUseFont({ 1350,40 }, color.White, "S：チュートリアルSkip", FontSize::L);
			DrawFormatStringToHandle(1500, 690, color.White, font->Use(FontSize::L), "：%d枚", map.scoreCoin);
			DrawFormatStringToHandle(820, 170, color.White, font->Use(FontSize::L), "：%d回", player.GetActionCount());
			DrawFormatStringToHandle(1350, 170, color.White, font->Use(FontSize::L), "ボムによる破壊：%d個", map.GetBombBreakCount());

			DrawFormatStringToHandle(600, 70, color.White, font->Use(FontSize::L), "上のブロック３つ壊してみよう！", map.GetBombBreakCount());
			break;

		case Play:
			ui.Draw(camera.GetPos());
			map.Draw(camera.GetPos());
			player.Draw(camera.GetPos());
			timer.Draw({ 650,70 });


			//デバッグ
			DrawFormatStringToHandle(1500, 690, color.White, font->Use(FontSize::L), "：%d枚", map.scoreCoin);
			DrawFormatStringToHandle(820, 170, color.White, font->Use(FontSize::L), "：%d回", player.GetActionCount());
			DrawFormatStringToHandle(1350, 170, color.White, font->Use(FontSize::L), "ボムによる破壊：%d個", map.GetBombBreakCount());
			DrawFormatStringToHandle(950, 70, color.White, font->Use(FontSize::L), "ステージ：%d", map.GetStage());
			break;

		case Result:
			font->DrawUseFont({ 750,150 }, color.White, "リザルト", FontSize::LL);
			DrawFormatStringToHandle(750, 350, color.White, font->Use(FontSize::LL), "スコア:%d", score);
			font->DrawUseFont({ 800,900 }, color.White, "SPACEで次へ", FontSize::L);
			break;

		case Ranking:

			font->DrawUseFont({ 650,150 }, color.White, "ランキング", FontSize::LL);
			ranking.Draw(*font);
			font->DrawUseFont({ 700,900 }, color.White, "SPACEでタイトルへ", FontSize::L);
			break;
		}
		scene.DrawCurtain();

#pragma endregion
		ScreenFlip();
		// 20ミリ秒待機(疑似60FPS)
		WaitTimer(20);
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