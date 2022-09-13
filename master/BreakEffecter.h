#pragma once
#include "DebriEmitter.h"

struct BreakEffect
{
	DebriEmitter debris;
	int timer = 0;
};

class BreakEffecter
{
private:
	std::vector<BreakEffect> effects;
	int debriG[2]{};
	bool isDeath = false;
	Vector2Int* leftTop;
public:
	void Load();
	void Initialize();
	void Emit(const Vector2Int& num, const int blockName);
	void Update();
	void Draw(const Vector2Int& camera);
	void SetLeftTop(Vector2Int* leftTop);
};

