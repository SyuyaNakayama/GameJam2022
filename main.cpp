#include "DxLib.h"
#include "Vector2.h"
#include "Input.h"
#include "function.h"

// ウィンドウのサイズ
const Vector2Int WIN_SIZE = { 800,800 };

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	SetOutApplicationLogValidFlag(false);
	ChangeWindowMode(TRUE);
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);
	SetMainWindowText("GameJam2022");
	SetGraphMode(WIN_SIZE.x, WIN_SIZE.y, 32);
	SetWindowSizeExtendRate(1.0);
	SetDrawScreen(DX_SCREEN_BACK);

	if (DxLib_Init() == -1)return -1;

	// ---定数の宣言と初期化---
	const int
		WHITE = GetColor(255, 255, 255),
		BOX_NUM = 9,
		OFFSET = 200,
		BOX_RAD = 16;

	// ---変数の宣言と初期化---
	Input input;
	Vector2Int pleyerPos = { 0,8 };

	while (!(ProcessMessage() == -1 || CheckHitKey(KEY_INPUT_ESCAPE)))
	{
		ClearDrawScreen();

		input.UpdateKeyState();

		pleyerPos.y += (input.isTrigger(KEY_INPUT_DOWN)) - input.isTrigger(KEY_INPUT_UP);
		pleyerPos.x += (input.isTrigger(KEY_INPUT_RIGHT)) - input.isTrigger(KEY_INPUT_LEFT);
		Clamp(pleyerPos.x, BOX_NUM - 1);
		Clamp(pleyerPos.y, BOX_NUM - 1);

		for (size_t y = 0; y < BOX_NUM; y++)
		{
			for (size_t x = 0; x < BOX_NUM; x++)
			{
				int fillFlag = (pleyerPos.x == x && pleyerPos.y == y);
				Vector2Int boxPos = Vector2Int(OFFSET, OFFSET) + Vector2Int(2 * BOX_RAD * x, 2 * BOX_RAD * y);
				DrawBoxWithVectorInt(boxPos, { BOX_RAD ,BOX_RAD }, WHITE, fillFlag);
			}
		}

		ScreenFlip();
	}

	// 全リソースファイル削除
	InitGraph();
	InitSoundMem();

	DxLib_End();
	return 0;
}