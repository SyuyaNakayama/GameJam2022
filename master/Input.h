#pragma once
#include "Keys.h"
#include "Pad.h"

class Input
{
public:
	Pad* pad = nullptr;
	Keys* keys = nullptr;
	enum Connect
	{
		Keyboard,
		JoyPad,
	};
	int connect = 0;
public:
	void Load();
	void ReSetup();
	void Update();
	bool IsRight();
	bool IsLeft();
	bool IsUp();
	bool IsDown();
	bool IsMove();
	bool IsSelect(); // B SPACE
	bool IsDone();   // Y ENTER
	bool IsCancel(); // A SHIFT
	bool IsSkip();   // X S
	int GetConnect() { return connect; }
public:
	static Input* GetInstance();
private:
	Input() = default;
	~Input() = default;
	Input(const Input&) = delete;
	const Input& operator=(const Input&) = delete;
};