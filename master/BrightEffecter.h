#pragma once
#include "BrightDraw.h"
#include <vector>

struct BrightEffect
{
	BrightDraw bright;
	int timer = 0;
};

class BrightEffecter
{
private:
	std::vector<BrightEffect> effects;
	int brightM[2]{};
	int whiteG = 0;
	bool isDeath = false;
	bool bright = false;
	int timer = 0;
	Vector2Int* leftTop;
public:
	void Load();
	void Initialize();
	void Emit(const Vector2Int& num);
	void Erase(const Vector2Int& num);
	void Clear();
	void Update();
	void Bright();
	void Draw(const Vector2Int& camera);
	void SetLeftTop(Vector2Int* leftTop);
};

