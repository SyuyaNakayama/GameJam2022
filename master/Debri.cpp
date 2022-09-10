#include "Debri.h"
#include "DxLib.h"

Debri::Debri() :
	speed(), isDeath(false), color(), graph(0)
{}

void Debri::Initialize(const Vector2Int& pos, const float scale, const float rota,
	const Vector2Int speed, const Color color, const int graph)
{
	this->pos = pos;
	this->scale = scale;
	this->rota = rota;
	this->trans = 255;
	this->speed = speed;
	isDeath = false;
	this->color = color;
	this->graph = graph;
}

void Debri::Update()
{
	if (isDeath) { return; }
	pos += speed;
	speed.y += 1;

	if (speed.x > 0) rota += DX_PI_F / 64.0f;
	if (speed.x < 0) rota -= DX_PI_F / 64.0f;

	scale += 0.1f;

	trans -= 15;
	if (trans <= 0)
	{
		trans = 0;
		isDeath = true;
	}
}

void Debri::Draw(const Vector2Int& camera)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, trans);
	SetDrawBright(color.r, color.g, color.b);
	DrawRotaGraph(pos.x, pos.y, scale, rota, graph, true);
	SetDrawBright(255, 255, 255);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
