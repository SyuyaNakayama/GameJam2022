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
	SetMainWindowText("GameJam2022_�V�̐l�A�̌@��ɂāB�`�A���b�q�̒n���z��`");
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
	int stage = 0, score = 0;
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
			player.Move();
			player.Destroy();
			if (input.IsTrigger(KEY_INPUT_R))
			{
				map.Create();
				player.SetPos({ rand() % 2 + 4,rand() % 2 + 4 });
				map.Change(player.GetPos(), None);
			}
			map.Update();
			if (player.GetActionCount() <= 0 || timer.CountDown(player.GetDamageCount())) { scene = GameOver; SetFontSize(96); }
			break;
		case GameOver:
			break;
		}
		camera.Update();
		pad->Update();
#pragma endregion
#pragma region �`�揈��
		switch (scene)
		{
		case Title:
			DrawString(50, 150, "�V�̐l�A�̌@��ɂāB\n\n�@�`�A���b�q�̒n���z��`", color.White);
			break;
		case Tutorial:
			break;
		case Play:
			map.Draw(camera.GetPos());
			player.Draw();
			timer.Draw({ 0,32 });
			DrawFormatString(0, 0, color.White, "�R�C���c��%d��", map.CountBlockNum(CoinBlock));
			DrawFormatString(400, 0, color.White, "�s����:%d��", player.GetActionCount());
			break;
		case GameOver:
			DrawString(50, 150, "�ċ�ցA�Q�[���I�[�o�[", color.White);
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