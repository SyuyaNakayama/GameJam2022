#pragma once
#include "Vector2.h"
#include "Ease.h"

class ArrowDraw
{
private:
	Vector2Int pos;
	Vector2Int number;
	float scale;
	float rota;
	int direction;
	Ease2 ease;
	int timer;
	bool change;

	int trans;
	int shadow;
	int* brightness;

	int arrowG[2]{};

	Vector2Int* playerPos;
public:
	ArrowDraw();
	void Initialize(const Vector2Int& leftTop, const Vector2Int& num, const int direction, const int arrowG[2]);
	void Update();
	void Draw(const Vector2Int& camera);
	void SetBrightness(int* brightness);
	void SetPlayerPos(Vector2Int* playerPos);
	Vector2Int GetNumber() { return number; }
private:
	void ChangeDirection(const int direction);
	void UpdateShadow();
};

