#pragma once
#include "DustEmitter.h"

struct DustEffect
{
	DustEmitter dusts;
	int timer = 0;
};

class DustEffecter
{
private:
	std::vector<DustEffect> effects;
	int dustG = 0;
	bool isDeath = false;
	Vector2Int* leftTop;
public:
	void Load();
	void Emit(const Vector2Int& num, const int blockName);
	void Update();
	void Draw(const Vector2Int& camera);
	void SetLeftTop(Vector2Int* leftTop);
};

