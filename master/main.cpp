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
#include "WindowSize.h"

using namespace std;

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
	// ��
	SoundManager* sound = SoundManager::GetInstance();
	sound->Load();

	// �V�[��
	SceneManager scene;
	scene.Initialze(Scene::Result, WIN_SIZE);

	// ---�萔�̐錾�Ə�����---

	Color color;
	// ---�ϐ��̐錾�Ə�����---
	Font* font = Font::GetInstance();
	font->Load();

	Input* input = Input::GetInstance();
	input->Load();

	int score = 0;

	int tutorialMessage = 0;

	bool menu = false;

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

	int rankingStringOffset = WIN_SIZE.x;
	int resultStringOffset = 0;
	const int STRING_MOVE_SPD = rankingStringOffset / 30;

	SetFontSize(48);

	while (!(ProcessMessage() == -1 || CheckHitKey(KEY_INPUT_ESCAPE)))
	{
#pragma region �X�V����
		ClearDrawScreen();

		input->Update();
		switch (scene.GetScene())
		{
			// --- �^�C�g�� --- //
		case Title:
			sound->PlayBGM(0);
			if (input->IsSelect()) scene.Change(Prologue);
			if (scene.IsChanged())
			{
				sound->StopBGM(0);
				input->ReSetup();
			}
			break;

			// --- �v�����[�O --- //
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

				bool next = prologueFontColor.back() >= 150 && input->IsSelect() || input->IsSkip();
				if (next) scene.Change(Tutorial);
			}

			if (scene.IsChanged())
			{
				score = 0;
				map.CreateTutorial();
				player.Reset({ 4,4 }, Up);
				sound->StopBGM(1);
				input->ReSetup();
			}
			break;

			// --- �`���[�g���A�� --- //
		case Tutorial:
			sound->PlayBGM(2);

			player.Update();
			if (input->keys->IsTrigger(KEY_INPUT_R))
			{
				map.CreateTutorial();
				player.Reset({ 4,4 }, Up);
			}

			map.Update();

			if (map.CountBlockNum(CoinBlock) == 0 && map.CountBlockNum(CrystalBlock) == 2)
			{
				tutorialMessage = 1;
				if (map.CountBlockNum(BombBlock) == 0)
				{
					tutorialMessage = 2;
				}
			}

			if (map.IsChange() || input->IsSkip()) scene.Change(Play);
			if (scene.IsChanged())
			{
				score = 0;
				menu = false;
				map.Create(true);
				player.Reset({ rand() % 2 + 4, rand() % 2 + 4 }, Up);
				ui.Initialize();
				timer.Reset();
				sound->StopBGM(2);
				input->ReSetup();
			}

			ui.Update();

			break;

			// --- �Q�[�� --- //
		case Play:
			sound->PlayBGM(3);

			if (menu == false)
			{
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
					input->ReSetup();
				}

				ui.Update();

				if (input->keys->IsTrigger(KEY_INPUT_S))
				{
					menu = true;
				}
			}
			else if (menu == true)
			{
				if (input->IsSelect())
				{
					scene.Change(Result);
					score = (map.scoreCoin * 100) * (1 + (0.1 * map.GetStage())) + (map.GetBombBreakCount() * 50);
					ui.Initialize();
					timer.Reset();
					sound->StopBGM(3);
				}

				if (input->keys->IsTrigger(KEY_INPUT_S))
				{
					menu = false;
				}
			}

			break;

			// --- ���U���g --- //
		case Result:
			sound->PlayBGM(4);
			if (input->IsSelect())
			{
				scene.SetScene(Ranking);
				ranking.Update(score);
			}
			break;

		case Ranking:
			if (rankingStringOffset > 0)
			{
				rankingStringOffset -= STRING_MOVE_SPD;
				resultStringOffset += STRING_MOVE_SPD;
				Clamp(rankingStringOffset, WIN_SIZE.x);
				Clamp(resultStringOffset, WIN_SIZE.x);
			}
			if (input->IsSelect()) scene.Change(Title);
			if (scene.IsChanged()) 
			{
				sound->StopBGM(4);
				input->ReSetup();
			}
			break;
		}
		camera.Update();
		scene.Update();
#pragma endregion
#pragma region �`�揈��
		switch (scene.GetScene())
		{
		case Title:
			font->DrawCenterXLine(150, color.White, "�V�̐l�A�̌@��ɂāB", FontSize::LL);
			font->DrawCenterXLine(150 + font->GetFontSize(FontSize::LL) + 10, color.White, "�`�A���b�q�̒n���z��`", FontSize::LL);
			font->DrawCenterXLine(650, color.White, "PRESS START", FontSize::L);
			break;

		case Prologue:
			for (int i = 0; i < prologueFontColor.size(); i++)
			{
				font->DrawCenterXLine(200 + (font->GetFontSize(FontSize::M) + 5) * i,
					GetColor(prologueFontColor[i], prologueFontColor[i], prologueFontColor[i]),
					prologueString[i], FontSize::M);
			}
			font->DrawUseFont({ 1750,40 }, color.White, "S�FSkip", FontSize::M);
			break;

		case Tutorial:
			ui.DrawTutorial(camera.GetPos());
			map.Draw(camera.GetPos());
			player.Draw(camera.GetPos());

			font->DrawUseFont({ 1400,40 }, color.White, "S�F�`���[�g���A��Skip", FontSize::M);
			DrawFormatStringToHandle(1000, 160, color.White, font->Use(FontSize::M), "�F%d��", map.scoreCoin);
			DrawFormatStringToHandle(750, 160, color.White, font->Use(FontSize::M), "�F%d��", player.GetActionCount());
			DrawFormatStringToHandle(1350, 770, color.White, font->Use(FontSize::M), "�{���ɂ��j��F%d��", map.GetBombBreakCount());
			if (tutorialMessage == 0)
			{
				font->DrawUseFont({ 600, 70 }, color.White, "��̃u���b�N�R�󂵂Ă݂悤�I", FontSize::M);
			}
			else if (tutorialMessage == 1)
			{
				font->DrawUseFont({ 600, 70 }, color.White, "�{���u���b�N���󂵂Ă݂悤�I", FontSize::M);
			}
			else if (tutorialMessage == 2)
			{
				font->DrawUseFont({ 600, 70 }, color.White, "�N���X�^�������߂悤�I", FontSize::M);
			}

			break;

		case Play:
			if (menu == false)
			{
				ui.DrawPlay(camera.GetPos());
				map.Draw(camera.GetPos());
				player.Draw(camera.GetPos());
				timer.Draw({ 650,70 });

				//�f�o�b�O
				DrawFormatStringToHandle(1000, 160, color.White, font->Use(FontSize::M), "�F%d��", map.scoreCoin);
				DrawFormatStringToHandle(750, 160, color.White, font->Use(FontSize::M), "�F%d��", player.GetActionCount());
				DrawFormatStringToHandle(1350, 770, color.White, font->Use(FontSize::M), "�{���ɂ��j��F%d��", map.GetBombBreakCount());
				DrawFormatStringToHandle(950, 70, color.White, font->Use(FontSize::M), "�X�e�[�W�F%d", map.GetStage());
				font->DrawUseFont({ 1700,40 }, color.White, "S�FMENU", FontSize::M);
			}
			else if (menu == true)
			{
				font->DrawUseFont({ 850, 150 }, color.White, "MENU", FontSize::LL);
				font->DrawUseFont({ 550, 350 }, color.White, "SPACE�F���U���g��", FontSize::LL);
				font->DrawUseFont({ 600, 650 }, color.White, "S�F�Q�[���ɖ߂�", FontSize::LL);
			}

			break;

		case Result:
		case Ranking:

			font->DrawCenterXLine(120, color.White, "���U���g", FontSize::L,-resultStringOffset);
			font->DrawCenterXLine(830, color.White, "SPACE�Ŏ���", FontSize::M, -resultStringOffset);
			font->DrawFormatCenterXLine(350, color.White, "�X�R�A:%d", FontSize::L, score, -resultStringOffset);

			font->DrawCenterXLine(120, color.White, "�����L���O", FontSize::L, rankingStringOffset);
			ranking.Draw({ rankingStringOffset,300 }, * font);
			font->DrawCenterXLine(830, color.White, "SPACE�Ń^�C�g����", FontSize::M, rankingStringOffset);
			break;
		}
		scene.DrawCurtain();

#pragma endregion
		ScreenFlip();
		// 20�~���b�ҋ@(�^��60FPS)
		WaitTimer(20);
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