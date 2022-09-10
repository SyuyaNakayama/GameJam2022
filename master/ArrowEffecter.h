#pragma once
#include "ArrowDraw.h"
#include <vector>

struct ArrowEffect 
{
	ArrowDraw arrow;
	int timer = 0;
};

class ArrowEffecter
{
private:
	std::vector<ArrowEffect> effects;
	int arrowG[2]{};
	bool isDeath = false;
	Vector2Int* leftTop;
public:
	void Load();
	void Emit(const Vector2Int& num, const int direction, int* brightness, Vector2Int* playerPos);
	void Erase(const Vector2Int& num);
	void Crear();
	void Update();
	void Draw(const Vector2Int& camera);
	void SetLeftTop(Vector2Int* leftTop);
};

