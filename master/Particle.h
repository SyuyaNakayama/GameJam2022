#pragma once
#include "Vector2.h"

class Particle
{
public:
	Vector2Int pos;
	float scale;
	float rota;
	struct Color
	{
		int r = 0;
		int g = 0;
		int b = 0;
	};
	Color color;
	int trans;
public:
	Particle();
};

