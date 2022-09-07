#pragma once
#include "DxLib.h"

class Pad
{
private:
	DINPUT_JOYSTATE* pad;
	DINPUT_JOYSTATE* oldpad;

	// �X�e�B�b�N����p (0 �` 1000)
	const int DOWN = 600;
public:
	Pad();
	~Pad();
	void Update();

	// �X�e�B�b�N����
	bool Right();
	bool Left();
	bool Up();
	bool Down();
	int Horizontal();
	int Vertical();

	// �{�^������
	enum Button { A, B, X, Y };
	bool IsTrigger(const int button);
};
