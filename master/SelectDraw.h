#pragma once
#include "Vector2.h"

class SelectDraw
{
private:
	Vector2Int leftTop;
	int setG = 0;
public:
	void Load();
	void Initialize(const Vector2Int& leftTop);
	void Update();
	void ChoseDraw(const Vector2Int& pos, const Vector2Int& camera);
	void Draw(const Vector2Int& pos, const Vector2Int& camera);
private:
	void SetCompDraw(const Vector2Int& center);
	void SetDraw(const Vector2Int& center);
};

