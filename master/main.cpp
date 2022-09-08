#include "DxLib.h"
#include "Vector2.h"
#include "Input.h"
#include "function.h"
#include "Map.h"
#include "Player.h"
#include <vector>
#include <stdlib.h>
#include <time.h>

using namespace std;

// �E�B���h�E�̃T�C�Y
const Vector2Int WIN_SIZE = { 1280,1280 * 2 / 3 };

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
#pragma region DXlib�����ݒ�
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
	enum Scene { Title, Tutorial, Play, GameOver };
	Scene scene = Scene::Play;

	const vector<Vector2Int>MAP_SIZE =
	{
		{9,9},
		{9,9},
		{9,9},
		{9,9}
	};

	const int STAGE_NUM = MAP_SIZE.size();

	Color color;
	// ---�ϐ��̐錾�Ə�����---
	Map map = Vector2Int(9, 9);
	for (int i = 0; i < 9; i++)
	{
		map.Change({ 0,i }, BlockName::Block);
		map.Change({ 8,i }, BlockName::Block);
		map.Change({ i,0 }, BlockName::Block);
		map.Change({ i,8 }, BlockName::Block);
	}

	Player player = { {3,3},32,&map };

	SetFontSize(96);

	while (!(ProcessMessage() == -1 || CheckHitKey(KEY_INPUT_ESCAPE)))
	{
#pragma region �X�V����
		ClearDrawScreen();

		switch (scene)
		{
		case Title:
			break;
		case Tutorial:
			break;
		case Play:
			player.Move();
			player.Destroy();
			break;
		case GameOver:
			break;
		}
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
			map.Draw();
			player.Draw();
			break;
		case GameOver:
			break;
		default:
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