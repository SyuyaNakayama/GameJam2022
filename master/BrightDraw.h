#pragma once
#include "Vector2.h"
#include "Ease.h"

class BrightDraw
{
private:
	Vector2Int pos;
	Vector2Int number;

	Vector2Int topL;
	Vector2Int topR;
	Vector2Int btmL;
	Vector2Int btmR;

	bool bright;

	Ease2 ease;

	bool corner1;
	bool finish1;
	bool corner2;
	bool finish2;

	int trans;

	int brightM[2]{};
	int whiteG;
public:
	BrightDraw();
	void Initialize(const Vector2Int& leftTop, const Vector2Int& num, const int brightM[2], const int whiteG);
	void Bright();
	void Update();
	void Draw(const Vector2Int& camera);
	Vector2Int GetNumber() { return number; }
private:
	void MoveBright();
};

