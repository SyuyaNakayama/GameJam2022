#include "Camera.h"

Camera::Camera() :
	pos(), shake()
{
	shake.Initialize();
}

void Camera::Initialize(const Vector2Int& pos)
{
	this->pos = pos;
	shake.Initialize();
}

void Camera::Update()
{
	shake.Update();
}

void Camera::Shaking(const int swing, const int dekey)
{
	shake.Shaking(swing, dekey);
}

Vector2Int Camera::GetPos()
{
	return pos + shake.GetValue();
}
