#pragma once
#include "DxLib.h"

class Pad
{
private:
	DINPUT_JOYSTATE* pad;
	DINPUT_JOYSTATE* oldpad;

	// スティック操作用 (0 ～ 1000)
	const int DOWN = 600;
public:
	Pad();
	~Pad();
	void Update();

	// スティック操作
	bool Right();
	bool Left();
	bool Up();
	bool Down();
	int Horizontal();
	int Vertical();

	// ボタン操作
	enum Button { A, B, X, Y };
	bool IsTrigger(const int button);
};