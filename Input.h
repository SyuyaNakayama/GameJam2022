#pragma once
#include "DxLib.h"

class Input
{
private:
	char key[256]{}, oldkey[256]{};
public:
	void UpdateKeyState();
	bool isInput(const int KEY_NUM);
	bool isTrigger(const int KEY_NUM);
};