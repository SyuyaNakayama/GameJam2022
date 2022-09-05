#include "Input.h"
#include "DxLib.h"
void Input::UpdateKeyState()
{
	for (size_t i = 0; i < 256; i++) { oldkey[i] = key[i]; };
	GetHitKeyStateAll(key);
}
bool Input::isInput(const int KEY_NUM) { return key[KEY_NUM]; };
bool Input::isTrigger(const int KEY_NUM) { return key[KEY_NUM] && !oldkey[KEY_NUM]; }