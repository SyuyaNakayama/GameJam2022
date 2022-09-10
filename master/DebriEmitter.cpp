#include "DebriEmitter.h"
#include "Random.h"

DebriEmitter::DebriEmitter() :
	debris(), isDeath(false)
{}

DebriEmitter::~DebriEmitter()
{
	debris.clear();
}

void DebriEmitter::Emit(const Vector2Int& leftTop, const Vector2Int& rightBottom, const size_t num,
					const Debri::Color color[2], const int graph)
{
	debris.clear();
	isDeath = false;
	for (size_t i = 0; i < num; i++)
	{
		Debri debri;
		Vector2Int pos = { GetRand(leftTop.x, rightBottom.x), GetRand(leftTop.y, rightBottom.y) };
		float scale = GetRandF(0.5f, 1.5f);
		float rota = GetRandF(0, 3.141592f * 2.0f);
		Vector2Int speed = { GetRand(-5, 5), GetRand(-10, 0) };
		int ary = GetRand(0, 1);
		Debri::Color c = color[ary];

		debri.Initialize(pos, scale, rota, speed, c, graph);

		debris.push_back(debri);
	}
}

void DebriEmitter::Update()
{
	size_t count = 0;
	for (size_t i = 0; i < debris.size(); i++)
	{
		if (debris[i].isDeath) count++;
		if (count >= debris.size())
		{
			isDeath = true;
			debris.clear();
			return;
		}
		debris[i].Update();
	}
}

void DebriEmitter::Draw(const Vector2Int& camera)
{
	for (size_t i = 0; i < debris.size(); i++)
	{
		if (!isDeath) debris[i].Draw(camera);
	}
}
