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
	Scene scene = Scene::Play;
	Color color;
	// ---�ϐ��̐錾�Ə�����---
	int stage = 1, score = 0;
	int scoreCoin = 0;
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
#pragma region �X�V����
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
			if (stage == 1 || stage == 2 || stage == 3)
			{
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
					map.DrawBright();
				}
				map.Update();
				if (map.CountBlockNum(CrystalBlock) == 0) {
					stage++;
					player.ActionReset();
					scoreCoin += 7 - map.CountBlockNum(CoinBlock);
					map.Create();
					player.SetPos({ rand() % 2 + 4,rand() % 2 + 4 });
					map.Change(player.GetPos(), None);
					map.SetBrightness(player.GetActionCount());
				}
			}
			if (player.GetActionCount() <= 0 || timer.CountDown(player.GetDamageCount())) { scene = GameOver; SetFontSize(96); }
			break;
		case GameOver:
			score = (scoreCoin * 100) * (1 + (0.1 * stage)) + (map.GetBombBreakCount() * 50);
			break;
		}
		camera.Update();
		pad->Update();
#pragma endregion
#pragma region �`�揈��
		switch (scene)
		{
		case Title:
			DrawString(50, 150, "�R�m�q�g�A�T�C�N�c�W���E�j�e�B", color.White);
			break;
		case Tutorial:
			break;
		case Play:
			if (stage == 1 || stage == 2 || stage == 3)
			{
				map.Draw(camera.GetPos());
				player.Draw();
				timer.Draw({ 0,32 });
				DrawFormatString(0, 0, color.White, "�R�C���c��%d��", map.CountBlockNum(CoinBlock));
				DrawFormatString(400, 0, color.White, "�s����:%d��", player.GetActionCount());
				DrawFormatString(400, 50, color.White, "�N���X�^��:%d��", map.CountBlockNum(CrystalBlock));
				DrawFormatString(400, 96, color.White, "�{���ɂ��j��:%d��", map.GetBombBreakCount());
			}
			DrawFormatString(800, 0, color.White, "�X�e�[�W:%d", stage);
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