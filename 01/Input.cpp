#include "Input.h"
#include "DxLib.h"
void Input::Update()
{
	for (size_t i = 0; i < 256; i++) { oldkey[i] = key[i]; };
	GetHitKeyStateAll(key);
}
bool Input::IsInput(const int KEY_NUM) { return key[KEY_NUM]; };
bool Input::IsTrigger(const int KEY_NUM) { return key[KEY_NUM] && !oldkey[KEY_NUM]; }

bool Input::IsTriggerMoveKey()
{
	return
		IsTrigger(KEY_INPUT_UP) ||
		IsTrigger(KEY_INPUT_DOWN) ||
		IsTrigger(KEY_INPUT_RIGHT) ||
		IsTrigger(KEY_INPUT_LEFT);
}