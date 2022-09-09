#pragma once
#include "Vector2.h"
#include "Ease.h"

class ArrowDraw
{
private:
	float scale;
	float rota;
	int direction;
	Ease2 ease;
	int timer;
	bool change;
	int trans;
	int arrowG;
public:
	ArrowDraw();
	void Initialize(const int direction, const int arrowG);
	void Update();
	void Draw(const Vector2Int& pos, const Vector2Int& camera, const int trans);
private:
	void ChangeDirection(const int direction);
};

