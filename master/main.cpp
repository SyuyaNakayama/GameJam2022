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
#include <string>

using namespace std;

// �E�B���h�E�̃T�C�Y
const Vector2Int WIN_SIZE = { 1280,1280 * 2 / 3 };

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
#pragma region �����ݒ�
	SetOutApplicationLogValidFlag(false);
	ChangeWindowMode(TRUE);
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);
	SetMainWindowText("GameJam2022_�R�m�q�g�A�T�C�N�c�W���E�j�e�B");
	SetGraphMode(WIN_SIZE.x, WIN_SIZE.y, 32);
	SetWindowSizeExtendRate(1.0);
	SetDrawScreen(DX_SCREEN_BACK);
	if (DxLib_Init() == -1) { return -1; }
	srand(time(0));
#pragma endregion
	// ---�萔�̐錾�Ə�����---
	Scene scene = Scene::Title;
	Color color;
	// ---�ϐ��̐錾�Ə�����---
	int score = 0;
	int scoreCoin = 0;

	Camera camera;
	camera.Initialize({});

	Map map;
	map.Create();

	Player player = { {rand() % 2 + 4,rand() % 2 + 4},&map };

	map.Change(player.GetPos(), None);
	map.drawer.ChipInit(player.GetPos(), None);
	map.SetOutSide(&camera, player.GetPosAdress());

	Timer timer = { GetNowCount() ,120 };
	Input input;
	Pad* pad = Pad::GetInstance();

	int fontSize = 48;
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

		input.Update();
		switch (scene)
		{
		case Title:
			if (input.IsTrigger(KEY_INPUT_SPACE)) { scene = Prologue; }
			break;
		case Prologue:
			for (size_t i = 0; i < prologueFontColor.size(); i++)
			{
				const int INC_NUM = 4;
				if (i == 0) { prologueFontColor[i] += INC_NUM; }
				else { if (prologueFontColor[i - 1] >= 200) { prologueFontColor[i] += INC_NUM; } }
				Clamp(prologueFontColor[i], 255);
			}
			if (prologueFontColor.back() >= 150 && input.IsTrigger(KEY_INPUT_SPACE)) { scene = Tutorial; }
			break;
		case Tutorial:
			break;
		case Play:

			player.Move();
			player.Destroy();
			if (input.IsTrigger(KEY_INPUT_R))
			{
				map.Create();
				player.SetPos({ rand() % 2 + 4,rand() % 2 + 4 });
				map.Change(player.GetPos(), None);
			}
			if (input.IsTrigger(KEY_INPUT_N))
			{
				map.drawer.ChipBright();
			}
			map.Update();
			if (map.CountBlockNum(CrystalBlock) == 0)
			{
				map.NextStage();
				player.ActionReset();
				scoreCoin += 7 - map.CountBlockNum(CoinBlock);
				player.SetPos({ rand() % 2 + 4,rand() % 2 + 4 });
				map.Change(player.GetPos(), None);
				map.drawer.SetBrightness(player.GetActionCount());
				timer = { GetNowCount() ,120 };
			}

			if (player.GetActionCount() <= 0 || timer.CountDown(player.GetDamageCount())) { scene = GameOver; SetFontSize(96); }
			break;
		case GameOver:
			score = (scoreCoin * 100) * (1 + (0.1 * map.GetStage())) + (map.GetBombBreakCount() * 50);
			break;
		}
		camera.Update();
		pad->Update();
#pragma endregion
#pragma region �`�揈��
		switch (scene)
		{
		case Title:
			DrawString(50, 150, "�V�̐l�A�̌@��ɂāB�`�A���b�q�̒n���z��`", color.White);
			break;
		case Prologue:
			for (size_t i = 0; i < prologueFontColor.size(); i++)
			{
				DrawString(200, 200 + fontSize * i, prologueString[i].c_str(),
					GetColor(prologueFontColor[i], prologueFontColor[i], prologueFontColor[i]));
			}
			break;
		case Tutorial:
			break;
		case Play:

			map.Draw(camera.GetPos());
			player.Draw();
			timer.Draw({ 0,32 });
			DrawFormatString(0, 0, color.White, "�R�C���c��%d��", map.CountBlockNum(CoinBlock));
			DrawFormatString(400, 0, color.White, "�s����:%d��", player.GetActionCount());
			DrawFormatString(400, 50, color.White, "�N���X�^��:%d��", map.CountBlockNum(CrystalBlock));
			DrawFormatString(400, 96, color.White, "�{���ɂ��j��:%d��", map.GetBombBreakCount());

			DrawFormatString(800, 0, color.White, "�X�e�[�W:%d", map.GetStage());
			break;
		case GameOver:
			DrawString(400, 150, "���U���g", color.White);
			DrawFormatString(400, 350, color.White, "�X�R�A:%d", score);
			break;
		}

		ScreenFlip();
#pragma endregion
	}
#pragma region �I������
	// �S���\�[�X�t�@�C���폜
	InitGraph();
	InitSoundMem();
	DxLib_End();
	return 0;
#pragma endregion
}