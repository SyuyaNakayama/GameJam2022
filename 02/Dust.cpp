#include "Dust.h"
#include "DxLib.h"

Dust::Dust() :
	speed(0.0f, 0.0f), rad(0), isDeath(false), control(0)
{}

void Dust::Initialize(const Vector2Int& pos, const int rad,
	const Vector2Int speed, const int trans)
{
	this->pos = pos;
	this->rad = rad;
	this->speed = speed;
}

void Dust::Update()
{
	if (!isDeath)
	{
		pos += speed;
		control++;
		if (control >= 10)
		{
			rad++;
			control = 0;
		}
		trans -= 10;
		if (trans <= 0)
		{
			trans = 0;
			isDeath = true;
		}
	}
}

void Dust::Draw(const Vector2Int& camera)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, trans);
	DrawCircle(pos.x, pos.y, rad, GetColor(180, 200, 220), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
