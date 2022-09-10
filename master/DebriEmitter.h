#pragma once
#include "Debri.h"
#include <vector>

class DebriEmitter
{
private:
	std::vector<Debri> debris;
	bool isDeath;
public:
	DebriEmitter();
	~DebriEmitter();
	void Emit(const Vector2Int& leftTop, const Vector2Int& rightBottom, const size_t num,
			const Debri::Color color[2], const int graph);
	void Update();
	void Draw(const Vector2Int& camera);
	bool GetIsDeath() { return isDeath; }
};
