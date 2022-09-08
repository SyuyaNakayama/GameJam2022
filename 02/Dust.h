#pragma once
#include "Particle.h"

class Dust : public Particle
{
public:
	int rad;
	Vector2Int speed;
	bool isDeath;
	int control;
public:
	Dust();
	void Initialize(const Vector2Int& pos, const int rad,
		const Vector2Int speed, const int trans);
	void Update();
	void Draw(const Vector2Int& camera);
};

