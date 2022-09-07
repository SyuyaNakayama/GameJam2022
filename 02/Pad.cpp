#include "Pad.h"
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

void Pad::Update()
{
	*oldpad = *pad;
	GetJoypadDirectInputState(DX_INPUT_PAD1, pad);
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