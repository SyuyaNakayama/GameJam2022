#include "DustEmitter.h"
#include "Random.h"

DustEmitter::DustEmitter() :
	dusts(), isDeath(false)
{}

DustEmitter::~DustEmitter()
{
	dusts.clear();
}

void DustEmitter::Initialize()
{
	dusts.clear();
	isDeath = false;
}

void DustEmitter::Emit(const Vector2Int& leftTop, const Vector2Int& rightBottom, const size_t num,
	const Particle::Color color, const int graph)
{
	dusts.clear();
	isDeath = false;
	for (size_t i = 0; i < num; i++)
	{
		Dust dust;
		Vector2Int pos = { GetRand(leftTop.x, rightBottom.x), GetRand(leftTop.y, rightBottom.y) };
		float scale = GetRandF(0.5f, 1.5f);
		float rota = GetRandF(0, 3.141592f * 2.0f);
		Vector2Int speed = { GetRand(-2, 2), GetRand(-2, 0) };
		int trans = GetRand(150, 250);

		dust.Initialize(pos, scale, rota, speed, color, trans, graph);

		dusts.push_back(dust);
	}
}

void DustEmitter::Update()
{
	size_t count = 0;
	for (size_t i = 0; i < dusts.size(); i++)
	{
		if (dusts[i].isDeath) count++;
		if (count >= dusts.size())
		{
			isDeath = true;
			dusts.clear();
			return;
		}
		dusts[i].Update();
	}
}

void DustEmitter::Draw(const Vector2Int& camera)
{
	if (isDeath) return;
	for (size_t i = 0; i < dusts.size(); i++)
	{
		dusts[i].Draw(camera);
	}
}
