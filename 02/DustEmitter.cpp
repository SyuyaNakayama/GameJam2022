#include "DustEmitter.h"
#include "Random.h"

DustEmitter::DustEmitter() :
	dusts(), isDeath(false)
{}

DustEmitter::~DustEmitter()
{
	dusts.clear();
}

void DustEmitter::Emit(const Vector2Int& leftTop, const Vector2Int& rightBottom, const int num)
{
	dusts.clear();
	isDeath = false;
	for (size_t i = 0; i < num; i++)
	{
		Dust dust;
		Vector2Int pos = { GetRand(leftTop.x, rightBottom.x), GetRand(leftTop.y, rightBottom.y) };
		int rad = GetRand(3, 5);
		Vector2Int speed = { GetRand(-2, 2), GetRand(-2, 0) };
		int trans = GetRand(100, 200);

		dust.Initialize(pos, rad, speed, trans);

		dusts.push_back(dust);
	}
}

void DustEmitter::Update()
{
	int count = 0;
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

void DustEmitter::Draw(const Vector2Int& shake)
{
	for (size_t i = 0; i < dusts.size(); i++)
	{
		if (!isDeath) dusts[i].Draw(shake);
	}
}
