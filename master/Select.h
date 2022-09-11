#pragma once
#include "Vector2.h"
#include <vector>

class Select
{
private:
	Vector2Int pos;
	std::vector<Vector2Int> chose;

	int setG = 0;
	Vector2Int* leftTop = nullptr;
public:
	void Load();
	void Initialize(const Vector2Int& playerPos);
	void Update();
	void Draw(const Vector2Int& camera);
	void SetLeftTop(Vector2Int* leftTop);
};