#include "DxLib.h"
#include "Vector2.h"
#include "Input.h"
#include "function.h"
#include "Map.h"
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
	SetMainWindowText("GameJam2022");
	SetGraphMode(WIN_SIZE.x, WIN_SIZE.y, 32);
	SetWindowSizeExtendRate(1.0);
	SetDrawScreen(DX_SCREEN_BACK);
	if (DxLib_Init() == -1) { return -1; }
	srand(time(0));
#pragma endregion
	// ---�萔�̐錾�Ə�����---
	const vector<Vector2Int>MAP_SIZE =
	{
		{9,9},
		{9,9},
		{9,9},
		{9,9}
	};

	const int
		OFFSET = 200,
		BOX_RAD = 32,
		STAGE_NUM = MAP_SIZE.size(),
		PLAYER_SPD = 5;

	Color color;
	// ---�ϐ��̐錾�Ə�����---
	Input input;
	Vector2Int playerPos = { 700,600 };

	Map map = Vector2Int(9, 9);
	map.Change({ 0,2 }, BlockName::Block);

	while (!(ProcessMessage() == -1 || CheckHitKey(KEY_INPUT_ESCAPE)))
	{
#pragma region �X�V����
		ClearDrawScreen();
		input.UpdateKeyState();

		playerPos.x += (input.isInput(KEY_INPUT_RIGHT) - input.isInput(KEY_INPUT_LEFT)) * PLAYER_SPD;
		playerPos.y += (input.isInput(KEY_INPUT_DOWN) - input.isInput(KEY_INPUT_UP)) * PLAYER_SPD;
		Clamp(playerPos.x, map.GetMapPos().x + 2 * map.GetRadius() * (map.GetMapSize().x - 1), map.GetMapPos().x);
		Clamp(playerPos.y, map.GetMapPos().y + 2 * map.GetRadius() * (map.GetMapSize().y - 1), map.GetMapPos().y);
#pragma endregion
#pragma region �`�揈��
		map.Draw();
		DrawCircle(playerPos.x, playerPos.y, 32, color.Green);

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