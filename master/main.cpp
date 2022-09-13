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
	ChangeWindowMode(1);
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);
	SetMainWindowText("�V�̐l�A�̌@��ɂāB\n�@�`�A���b�q�̒n���z��`");
	SetGraphMode(WIN_SIZE.x, WIN_SIZE.y, 32);
	SetWindowSizeExtendRate(1.0);
	SetDrawScreen(DX_SCREEN_BACK);
	if (DxLib_Init() == -1) { return -1; }
#pragma endregion
	// BGM,SE�ǂݍ���
	vector<int>bgm =
	{
		LoadSoundMem("Resources/Sound/BGM/Title.mp3"),
		LoadSoundMem("Resources/Sound/BGM/Prologue.mp3"),
		LoadSoundMem("Resources/Sound/BGM/Tutrial.mp3"),
		LoadSoundMem("Resources/Sound/BGM/Play.mp3"),
	};

	// ---�萔�̐錾�Ə�����---
	Scene scene = Scene::Title;
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
	map.CreateTutorial();

	Player player;
	player.LoadAndSet(&map);
	player.Initialize({ rand() % 2 + 4,rand() % 2 + 4 }, Up);

	map.SetOutSide(&camera, player.GetPosAdress());
	map.Change(player.GetPos(), None);

	UIDrawer ui;
	ui.LoadAndSet(player.GetActionCountPointer(), &scoreCoin, &crystalCounter);
	ui.Initialize();

	Timer timer = { GetNowCount() ,100 };

	RankingManager ranking;
	ranking.Reset(); // ***** �f�o�b�O�p(��o���̓R�����g�A�E�g���邱�ƁI�I�I) ***** //
	ranking.Load();

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
	vector<int> prologueFontColor(prologueString.size(), 0);

	SetFontSize(48);

	while (!(ProcessMessage() == -1 || CheckHitKey(KEY_INPUT_ESCAPE)))
	{
#pragma region �X�V����
		ClearDrawScreen();

		input->Update();
		switch (scene)
		{
		// --- �^�C�g�� --- //
		case Title:
			if (input->keys->IsTrigger(KEY_INPUT_SPACE)) { scene = Prologue; }
			break;

		// --- �v�����[�O --- //
		case Prologue:
			for (size_t i = 0; i < prologueFontColor.size(); i++)
			{
				const int INC_NUM = 4;
				if (i == 0) { prologueFontColor[i] += INC_NUM; }
				else { if (prologueFontColor[i - 1] >= 200) { prologueFontColor[i] += INC_NUM; } }
				Clamp(prologueFontColor[i], 255);
			}
			if (prologueFontColor.back() >= 150 && input->keys->IsTrigger(KEY_INPUT_SPACE))
			{
				scene = Tutorial;
				map.CreateTutorial();
				player.Reset({ 4,4 }, Up);
				map.Change(player.GetPos(), None);
			}

			if (input->keys->IsTrigger(KEY_INPUT_S))
			{
				scene = Tutorial;
				map.CreateTutorial();
				player.Reset({ 4,4 }, Up);
				map.Change(player.GetPos(), None);
			}

			break;

		// --- �`���[�g���A�� --- //
		case Tutorial:

			player.Update();
			if (input->keys->IsTrigger(KEY_INPUT_R))
			{
				map.CreateTutorial();
				player.Reset({ 4,4 }, Up);
				map.Change(player.GetPos(), None);
			}

			map.Update();

			crystalCounter = map.CrystalRemain();

			if (crystalCounter == 3 || input->keys->IsTrigger(KEY_INPUT_S))
			{
				scene = Play;
				score = 0;
				scoreCoin = 0;
				map.Create();
				player.Reset({ rand() % 2 + 4, rand() % 2 + 4 }, Up);
				map.Change(player.GetPos(), None);
				timer.Reset();
			}

			break;

		// --- �Q�[�� --- //
		case Play:
			player.Update();
			if (input->keys->IsTrigger(KEY_INPUT_R))
			{
				map.Create();
				player.Reset({ rand() % 2 + 4,rand() % 2 + 4 }, Up);
				map.Change(player.GetPos(), None);
			}

			map.Update();

			scoreCoin = map.CoinUpdate();
			crystalCounter = map.CrystalRemain();

			if (crystalCounter == 3)
			{
				map.NextStage();
				if (map.GetStage() % 4 == 0)
				{
					player.Reset({ 4,4 }, Up);
				}
				else 
				{
					player.Reset({ rand() % 2 + 4,rand() % 2 + 4 }, Up);
				}
				map.Change(player.GetPos(), None);
				timer.Reset();
			}

			if (player.GetActionCount() <= 0 || timer.CountDown(player.GetDamageCount()))
			{
				score = (scoreCoin * 100) * (1 + (0.1 * map.GetStage())) + (map.GetBombBreakCount() * 50);
				scene = Result; 
			}

			ui.Update();
			break;

		// --- ���U���g --- //
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
			ui.Draw(camera.GetPos());
			map.Draw(camera.GetPos());
			player.Draw(camera.GetPos());
			font.DrawUseFont({ 750,50 }, color.White, "S�F�`���[�g���A��Skip", FontSize::L);
			break;

		case Play:
			ui.Draw(camera.GetPos());
			map.Draw(camera.GetPos());
			player.Draw(camera.GetPos());
			timer.Draw({ 0,32 });


			//�f�o�b�O
			DrawFormatStringToHandle(0, 0, color.White,font.Use(FontSize::L), "�R�C���c��%d��", map.CountBlockNum(CoinBlock));
			DrawFormatStringToHandle(400, 0, color.White,font.Use(FontSize::L), "�s����:%d��", player.GetActionCount());
			DrawFormatStringToHandle(400, 50, color.White,font.Use(FontSize::L), "�N���X�^��:%d��", map.CountBlockNum(CrystalBlock));
			DrawFormatStringToHandle(400, 96, color.White,font.Use(FontSize::L), "�{���ɂ��j��:%d��", map.GetBombBreakCount());
			DrawFormatStringToHandle(800, 0, color.White,font.Use(FontSize::L), "�X�e�[�W:%d", map.GetStage());
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