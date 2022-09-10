#include "Dust.h"
#include "DxLib.h"

Dust::Dust() :
	speed(0, 0), isDeath(false), timer(0), graph(0)
{}

void Dust::Initialize(const Vector2Int& pos, const float scale, const float rota, const Vector2Int speed,
	const Color color, const int trans, const int graph)
{
	this->pos = pos;
	this->scale = scale;
	this->rota = rota;
	this->speed = speed;
	this->color = color;
	this->trans = trans;
	this->graph = graph;
	this->timer = 0;
	this->isDeath = false;
}

void Dust::Update()
{
	if (isDeath) { return; }
	pos += speed;
	if (++timer >= 10)
	{
		scale += 0.1f;
		timer = 0;
	}
	trans -= 10;
	if (trans <= 0)
	{
		trans = 0;
		isDeath = true;
	}
}

void Dust::Draw(const Vector2Int& camera)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, trans);
	SetDrawBright(color.r, color.g, color.b);
	DrawRotaGraph(pos.x, pos.y, scale, rota, graph, true);
	SetDrawBright(255, 255, 255);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
