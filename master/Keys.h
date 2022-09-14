#pragma once
#include "Vector2.h"

class Keys
{
private:
	char* keys;
	char* oldkeys;

	int directionKeyG[4][2]{ {} };
	int keyG[2]{};
	int spaceKeyG[2]{};
	int shiftKeyG[2]{};
	int enterKeyG[2]{};

	bool downArrow[4] = { false, false, false, false };
	bool downS = false;
	bool downShift = false;
	bool downSpace = false;
	bool downEnter = false;
public:
	void Load();
	void Update();
	bool IsDown(const int key);
	bool IsTrigger(const int key);
	bool IsLongPress(const int key);
	bool IsRelease(const int key);
	int Horizontal();
	int Vertical();

	void DrawArrow(const Vector2Int& pos);
	void DrawUp(const Vector2Int& pos);
	void DrawDown(const Vector2Int& pos);
	void DrawLeft(const Vector2Int& pos);
	void DrawRight(const Vector2Int& pos);

	void DrawKey(const Vector2Int& pos);

	void DrawSpace(const Vector2Int& pos);
	void DrawShift(const Vector2Int& pos);
	void DrawEnter(const Vector2Int& pos);
public:
	static Keys* GetInstance();
private:
	Keys();
	~Keys();
	Keys(const Keys&) = delete;
	const Keys& operator=(const Keys&) = delete;
};

