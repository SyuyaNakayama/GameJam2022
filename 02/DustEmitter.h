#pragma once
#include "Dust.h"
#include <vector>

class DustEmitter
{
private:
	std::vector<Dust> dusts;
	bool isDeath;
public:
	DustEmitter();
	~DustEmitter();
	void Emit(const Vector2Int& leftTop, const Vector2Int& rightBottom, const int num);
	void Update();
	void Draw(const Vector2Int& shake);
};

