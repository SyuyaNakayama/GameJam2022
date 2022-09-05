#include "DxLib.h"
#include "Vector2.h"
#include "Input.h"
#include <cmath>
#include <vector>
#include <string>

using namespace std;

// ウィンドウのサイズ
const Vector2 WIN_SIZE = { 800.0f,800.0f };

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	ChangeWindowMode(TRUE);
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);
	SetMainWindowText("円グラフ演習");
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
	int fillFlag = 0;

	while (!(ProcessMessage() == -1 || CheckHitKey(KEY_INPUT_ESCAPE)))
	{
		ClearDrawScreen();

		input.UpdateKeyState();

		pleyerPos.y += (input.isTrigger(KEY_INPUT_DOWN)) - input.isTrigger(KEY_INPUT_UP);
		pleyerPos.x += (input.isTrigger(KEY_INPUT_RIGHT)) - input.isTrigger(KEY_INPUT_LEFT);

		for (size_t y = 0; y < BOX_NUM; y++)
		{
			for (size_t x = 0; x < BOX_NUM; x++)
			{
				fillFlag = (pleyerPos.x == x && pleyerPos.y == y);
				DrawBox(OFFSET + 32 * x - BOX_RAD, OFFSET + 32 * y - BOX_RAD, OFFSET + 32 * x + BOX_RAD, OFFSET + 32 * y + BOX_RAD, WHITE, fillFlag);
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