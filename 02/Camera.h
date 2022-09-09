#pragma once
#include "Shake.h"

class Camera
{
private:
	Vector2Int pos;
	Shake shake;
public:
	Camera();
	void Initialize(const Vector2Int& pos);
	void Update();
	void Shaking(const int swing, const int dekey);
	Vector2Int GetPos();
};

