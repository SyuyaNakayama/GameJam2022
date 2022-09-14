#include "Pad.h"

Pad* Pad::GetInstance()
{
	static Pad instance;
	return &instance;
}

Pad::Pad() :
	pad(new DINPUT_JOYSTATE), oldpad(new DINPUT_JOYSTATE)
{
	ReSetupJoypad();
	GetJoypadDirectInputState(DX_INPUT_PAD1, pad);
	GetJoypadDirectInputState(DX_INPUT_PAD1, oldpad);
}

Pad::~Pad()
{
	delete pad;
	pad = 0;
	delete oldpad;
	oldpad = 0;
}

void Pad::Load()
{
	stickG = LoadGraph("Resources/UI/stick.png");
	LoadDivGraph("Resources/UI/button_A.png", 2, 2, 1, 64, 64, buttonG[A]);
	LoadDivGraph("Resources/UI/button_B.png", 2, 2, 1, 64, 64, buttonG[B]);
	LoadDivGraph("Resources/UI/button_X.png", 2, 2, 1, 64, 64, buttonG[X]);
	LoadDivGraph("Resources/UI/button_Y.png", 2, 2, 1, 64, 64, buttonG[Y]);
}

void Pad::Update()
{
	*oldpad = *pad;
	GetJoypadDirectInputState(DX_INPUT_PAD1, pad);
	for (size_t i = 0; i < 4; i++)
	{
		downButton[i] = pad->Buttons[i] == 128;
	}
}

bool Pad::RightTrigger()
{
	return pad->X >= DOWN && oldpad->X >= 0;
}
bool Pad::LeftTrigger()
{
	return pad->X <= -DOWN && oldpad->X <= 0;
}
bool Pad::UpTrigger()
{
	return pad->Y <= -DOWN && oldpad->Y <= 0;
}
bool Pad::DownTrigger()
{
	return pad->Y >= DOWN && oldpad->Y >= 0;
}
bool Pad::Right()
{
	return pad->X >= DOWN && oldpad->X >= DOWN;
}
bool Pad::Left()
{
	return pad->X <= -DOWN && oldpad->X <= -DOWN;
}
bool Pad::Up()
{
	return pad->Y <= -DOWN && oldpad->Y <= -DOWN;
}
bool Pad::Down()
{
	return pad->Y >= DOWN && oldpad->Y >= DOWN;
}
int Pad::Horizontal()
{
	return Right() - Left();
}
int Pad::Vertical()
{
	return Up() - Down();
}

bool Pad::IsTrigger(const int button)
{
	if (Y < button || button < A) return false;
	return pad->Buttons[button] == 128 &&
		oldpad->Buttons[button] == 0;
}

void Pad::Viblation(const int power, const int time)
{
	int p = power, t = time;

	if (0 >= power) p = 0;
	if (1000 <= power) p = 1000;

	if (-1 >= time) t = -1;

	StartJoypadVibration(DX_INPUT_PAD1, p, t);
}
void Pad::StopViblation()
{
	StopJoypadVibration(DX_INPUT_PAD1);
}

void Pad::DrawStick(const Vector2Int& pos)
{
	DrawExtendGraph(pos.x, pos.y, pos.x + 128, pos.y + 128, stickG, true);
}
void Pad::DrawButton(const Vector2Int& pos)
{
	DrawA({ pos.x + 64, pos.y + 96 });
	DrawB({ pos.x + 128, pos.y + 48 });
	DrawX({ pos.x, pos.y + 48 });
	DrawY({ pos.x + 64, pos.y });
}
void Pad::DrawA(const Vector2Int& pos)
{
	DrawGraph(pos.x, pos.y, buttonG[A][downButton[A]], true);
}
void Pad::DrawB(const Vector2Int& pos, const int scale)
{
	DrawExtendGraph(pos.x, pos.y, pos.x + (64 * scale), pos.y + (64 * scale), buttonG[B][downButton[B]], true);
}
void Pad::DrawX(const Vector2Int& pos, const int scale)
{
	DrawExtendGraph(pos.x, pos.y, pos.x + (64 * scale), pos.y + (64 * scale), buttonG[X][downButton[X]], true);
}
void Pad::DrawY(const Vector2Int& pos)
{
	DrawGraph(pos.x, pos.y, buttonG[Y][downButton[Y]], true);
}