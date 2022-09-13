#pragma once
#include "Keys.h"
#include "Pad.h"

class Input
{
public:
	Pad* pad = nullptr;
	Keys* keys = nullptr;
public:
	void Load();
	void Update();
	bool IsRight();
	bool IsLeft();
	bool IsUp();
	bool IsDown();
	bool IsMove();
	bool IsSelect(); // B SPACE
	bool IsDone();   // Y ENTER
	bool IsCancel(); // A SHIFT
public:
	static Input* GetInstance();
private:
	Input() = default;
	~Input() = default;
	Input(const Input&) = delete;
	const Input& operator=(const Input&) = delete;
};