#pragma once
#include "Vector2.h"

class BrightDraw
{
private:
	Vector2Int topL;
	Vector2Int topR;
	Vector2Int btmL;
	Vector2Int btmR;

	bool bright;

	bool corner1;
	bool finish1;
	bool corner2;
	bool finish2;

	int maskG;
	int whiteG;
public:
	BrightDraw();
	void Initialize(const Vector2Int& size, const int maskG, const int whiteG);
	void Bright();
	void Update();
	void Draw(const Vector2Int& pos, const Vector2Int& camera, const int trans);
private:
	void MoveBright();
};

