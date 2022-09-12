#pragma once
#include "DxLib.h"
#include "Vector2.h"

class Pad
{
private:
	DINPUT_JOYSTATE* pad;
	DINPUT_JOYSTATE* oldpad;

	// スティック操作用 (0 ～ 1000)
	const int DOWN = 600;

	// 画像用
	int stickG = 0;
	int buttonG[4][2] = { { 0,0 }, { 0,0 }, { 0,0 }, { 0,0 } };
	bool downButton[4] = { false, false, false, false };
public:
	void Load();
	void Update();

	// スティック操作
	bool RightTrigger();
	bool LeftTrigger();
	bool UpTrigger();
	bool DownTrigger();
	bool Right();
	bool Left();
	bool Up();
	bool Down();
	int Horizontal();
	int Vertical();

	// ボタン操作
	enum Button
	{
		A,
		B,
		X,
		Y,
	};
	bool IsTrigger(const int button);

	// 振動
	// power (MAX 1000), time (1s = 1000, ∞ = -1) 
	void Viblation(const int power, const int time);
	void StopViblation();

	// 描画
	void DrawStick(const Vector2Int& pos);
	void DrawButton(const Vector2Int& pos);
	void DrawA(const Vector2Int& pos);
	void DrawB(const Vector2Int& pos);
	void DrawX(const Vector2Int& pos);
	void DrawY(const Vector2Int& pos);

public:
	static Pad* GetInstance();
private:
	Pad();
	~Pad();
	Pad(const Pad&) = delete;
	const Pad& operator=(const Pad&) = delete;
};