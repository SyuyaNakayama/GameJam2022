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
	// ��
	SoundManager* sound = SoundManager::GetInstance();
	sound->Load();

	// �V�[��
	SceneManager scene;
	scene.Initialze(Scene::Title, WIN_SIZE);

	// ---�萔�̐錾�Ə�����---

	Color color;
	// ---�ϐ��̐錾�Ə�����---
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
		switch (scene.GetScene())
		{
			// --- �^�C�g�� --- //
		case Title:
			sound->PlayBGM(0);
			if (input->IsSelect()) scene.Change(Prologue);
			if (scene.IsChanged()) sound->StopBGM(0);
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

			// --- �Q�[�� --- //
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
			if (input->IsSelect()) scene.Change(Title);
			if (scene.IsChanged()) sound->StopBGM(4);
			break;
		}
		camera.Update();
		scene.Update();
#pragma endregion
#pragma region �`�揈��
		switch (scene.GetScene())
		{
		case Title:
			font->DrawUseFont({ 80,150 }, color.White, "�V�̐l�A�̌@��ɂāB\n�@�`�A���b�q�̒n���z��`", FontSize::LL);
			font->DrawUseFont({ 370,450 }, color.White, "PRESS START", FontSize::LL);
			break;

		case Prologue:
			for (int i = 0; i < prologueFontColor.size(); i++)
			{
				font->DrawUseFont({ 200,200 + (font->GetFontSize(FontSize::L) + 5) * i },
					GetColor(prologueFontColor[i], prologueFontColor[i], prologueFontColor[i]),
					prologueString[i], FontSize::L);
			}
			font->DrawUseFont({ 1350,40 }, color.White, "S�FSkip", FontSize::L);
			break;

		case Tutorial:
			ui.Draw(camera.GetPos());
			map.Draw(camera.GetPos());
			player.Draw(camera.GetPos());
			font->DrawUseFont({ 1350,40 }, color.White, "S�F�`���[�g���A��Skip", FontSize::L);
			DrawFormatStringToHandle(1500, 690, color.White, font->Use(FontSize::L), "�F%d��", map.scoreCoin);
			DrawFormatStringToHandle(820, 170, color.White, font->Use(FontSize::L), "�F%d��", player.GetActionCount());
			DrawFormatStringToHandle(1350, 170, color.White, font->Use(FontSize::L), "�{���ɂ��j��F%d��", map.GetBombBreakCount());

			DrawFormatStringToHandle(600, 70, color.White, font->Use(FontSize::L), "��̃u���b�N�R�󂵂Ă݂悤�I", map.GetBombBreakCount());
			break;

		case Play:
			ui.Draw(camera.GetPos());
			map.Draw(camera.GetPos());
			player.Draw(camera.GetPos());
			timer.Draw({ 650,70 });


			//�f�o�b�O
			DrawFormatStringToHandle(1500, 690, color.White, font->Use(FontSize::L), "�F%d��", map.scoreCoin);
			DrawFormatStringToHandle(820, 170, color.White, font->Use(FontSize::L), "�F%d��", player.GetActionCount());
			DrawFormatStringToHandle(1350, 170, color.White, font->Use(FontSize::L), "�{���ɂ��j��F%d��", map.GetBombBreakCount());
			DrawFormatStringToHandle(950, 70, color.White, font->Use(FontSize::L), "�X�e�[�W�F%d", map.GetStage());
			break;

		case Result:
			font->DrawUseFont({ 750,150 }, color.White, "���U���g", FontSize::LL);
			DrawFormatStringToHandle(750, 350, color.White, font->Use(FontSize::LL), "�X�R�A:%d", score);
			font->DrawUseFont({ 800,900 }, color.White, "SPACE�Ŏ���", FontSize::L);
			break;

		case Ranking:

			font->DrawUseFont({ 650,150 }, color.White, "�����L���O", FontSize::LL);
			ranking.Draw(*font);
			font->DrawUseFont({ 700,900 }, color.White, "SPACE�Ń^�C�g����", FontSize::L);
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