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

// �E�B���h�E�̃T�C�Y
const Vector2Int WIN_SIZE = { 1920,980 };

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
#pragma region �����ݒ�
	SetOutApplicationLogValidFlag(false);
	ChangeWindowMode(TRUE);
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);
	SetMainWindowText("�V�̐l�A�̌@��ɂāB\n�@�`�A���b�q�̒n���z��`");
	SetGraphMode(WIN_SIZE.x, WIN_SIZE.y, 32);
	SetWindowSizeExtendRate(1.0);
	SetDrawScreen(DX_SCREEN_BACK);
	if (DxLib_Init() == -1) { return -1; }
#pragma endregion
	// ---�萔�̐錾�Ə�����---
	Scene scene = Scene::Play;
	Color color;
	// ---�ϐ��̐錾�Ə�����---
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
	ranking.Reset(); // �f�o�b�O�p
	ranking.Load();
	vector<int> prologueFontColor(8, 0);
	vector<string> prologueString =
	{
		"���͐���2173�N�A",
		"�A���b�q�ł�1�l�̒j��",
		"�A�N���X�̐l�Ԃ���",
		"�����J����������ꂽ�B",
		"�z�΂��������",
		"���ꂪ�����ɂȂ�B",
		"����Ȓj�̒n���̌@��ł̂��b�B",
		"\nSPACE�Ŏ��ց�"
	};
	SetFontSize(fontSize);
	while (!(ProcessMessage() == -1 || CheckHitKey(KEY_INPUT_ESCAPE)))
	{
#pragma region �X�V����
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
#pragma region �`�揈��
		switch (scene)
		{
		case Title:
			font.DrawUseFont({ 80,150 }, color.White, "�V�̐l�A�̌@��ɂāB\n�@�`�A���b�q�̒n���z��`", FontSize::LL);
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
			DrawFormatString(0, 0, color.White, "�R�C���c��%d��", map.CountBlockNum(CoinBlock));
			DrawFormatString(400, 0, color.White, "�s����:%d��", player.GetActionCount());
			DrawFormatString(400, 50, color.White, "�N���X�^��:%d��", map.CountBlockNum(CrystalBlock));
			DrawFormatString(400, 96, color.White, "�{���ɂ��j��:%d��", map.GetBombBreakCount());
			DrawFormatString(800, 0, color.White, "�X�e�[�W:%d", map.GetStage());
			break;
		case Result:
			font.DrawUseFont({ 400,150 }, color.White, "���U���g", FontSize::LL);
			DrawFormatStringToHandle(400, 350, color.White, font.Use(FontSize::LL), "�X�R�A:%d", score);
			break;
		case Ranking:
			DrawFormatStringToHandle(400, 100, color.White, font.Use(FontSize::LL), "�X�R�A:%d", score);
			ranking.Draw(font);
			break;
		}

		ScreenFlip();
		// 20�~���b�ҋ@(�^��60FPS)
		WaitTimer(20);
#pragma endregion
	}
#pragma region �I������
	// �S���\�[�X�t�@�C���폜
	InitGraph();
	InitSoundMem();
	InitFontToHandle();
	DxLib_End();
	return 0;
#pragma endregion
}