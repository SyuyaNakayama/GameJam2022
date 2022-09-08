#include "DxLib.h"
#include "Vector2.h"
#include "Input.h"
#include "Pad.h"
#include "function.h"
#include "DustEmitter.h"

// �E�B���h�E�̃T�C�Y
const Vector2Int WIN_SIZE = { 800,800 };

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
#pragma endregion
	// ---�萔�̐錾�Ə�����---
	const int
		WHITE = GetColor(255, 255, 255),
		BOX_NUM = 9,
		OFFSET = 200,
		BOX_RAD = 16;

	// ---�ϐ��̐錾�Ə�����---
	Input input;
	Vector2Int pleyerPos = { 0,8 };
	Pad* pad = Pad::GetInstance();
	pad->Load();
	int p = 0;
	DustEmitter dustE;

	while (!(ProcessMessage() == -1 || CheckHitKey(KEY_INPUT_ESCAPE)))
	{
#pragma region �X�V����
		ClearDrawScreen();
		input.UpdateKeyState();
		pad->Update();

		p += pad->Horizontal() * 10;
		if (pad->IsTrigger(Pad::A)) pad->Viblation(p, 1000);
		if (pad->IsTrigger(Pad::B)) dustE.Emit({ 100,100 }, { 200,100 }, 10);
		dustE.Update();

		pleyerPos.x += (input.isTrigger(KEY_INPUT_RIGHT)) - input.isTrigger(KEY_INPUT_LEFT);
		pleyerPos.y += (input.isTrigger(KEY_INPUT_DOWN)) - input.isTrigger(KEY_INPUT_UP);
		Clamp(pleyerPos.x, BOX_NUM - 1);
		Clamp(pleyerPos.y, BOX_NUM - 1);
#pragma endregion
#pragma region �`�揈��
		DrawBox(0, 0, WIN_SIZE.x, WIN_SIZE.y, GetColor(17, 28, 36), true);
		for (size_t y = 0; y < BOX_NUM; y++)
		{
			for (size_t x = 0; x < BOX_NUM; x++)
			{
				int fillFlag = (pleyerPos.x == x && pleyerPos.y == y);
				Vector2Int boxPos = Vector2Int(OFFSET, OFFSET) + Vector2Int(2 * BOX_RAD * x, 2 * BOX_RAD * y);
				DrawBoxWithVectorInt(boxPos, { BOX_RAD ,BOX_RAD }, WHITE, fillFlag);
			}
		}
		pad->DrawButton({ 0,0 });
		pad->DrawStick({ 128,128 });
		dustE.Draw({});

		DrawFormatString(0, 0, GetColor(255, 255, 0), "power = %d", p);

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