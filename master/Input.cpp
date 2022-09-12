#include "Input.h"
#include "DxLib.h"

Input* Input::GetInstance()
{
	static Input instance;
	return &instance;
}

void Input::Load()
{
	keys = Keys::GetInstance();
	pad = Pad::GetInstance();
	keys->Load();
	pad->Load();
}

void Input::Update()
{
	keys->Update();
	pad->Update();
}

bool Input::IsRight()
{
	return keys->IsTrigger(KEY_INPUT_RIGHT) || pad->RightTrigger();
}
bool Input::IsLeft()
{
	return keys->IsTrigger(KEY_INPUT_LEFT) || pad->LeftTrigger();
}
bool Input::IsUp()
{
	return keys->IsTrigger(KEY_INPUT_UP) || pad->UpTrigger();
}
bool Input::IsDown()
{
	return keys->IsTrigger(KEY_INPUT_DOWN) || pad->DownTrigger();
}
bool Input::IsMove()
{
	return 	IsRight() || IsLeft() || IsUp() || IsDown();
}