#pragma once
#include "Particle.h"

class Debri : public Particle
{
public:
	Vector2Int speed;
	bool isDeath;
	int graph;
public:
	Debri();
	void Initialize(const Vector2Int& pos, const float scale, const float rota, const Vector2Int speed, 
					const Color color, const int graph);
	void Update();
	void Draw(const Vector2Int& camera);
};

