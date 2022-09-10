#include "DustEffecter.h"
#include "enum.h"
#include "DrawParameter.h"

void DustEffecter::Load()
{
	dustG = LoadGraph("Resources/Block/dust.png");
}

void DustEffecter::Emit(const Vector2Int& num, const int blockName)
{
	if (!leftTop) return;
	DustEffect effect;
	Vector2Int p = { leftTop->x + num.x * 64, leftTop->y + num.y * 64 };
	Particle::Color c{};
	int g = dustG;
	switch (blockName)
	{
	case Block:
		c = { 150,210,220 };
		break;
	case CoinBlock:
		c = { 250,250,100 };
		break;
	case CrystalBlock:
		c = { 180,250,100 };
		break;
	case BombBlock:
		c = { 240,170,20 };
		break;
	case None:
		g = 0;
		break;
	}
	effect.dusts.Emit({ p.x - 32, p.y + 32 }, { p.x + 32, p.y + 32 }, 10, c, g);
	effect.timer = 0;
	effects.push_back(effect);
	isDeath = false;
}

void DustEffecter::Update()
{
	size_t count = 0;
	for (size_t i = 0; i < effects.size(); i++)
	{
		if (++effects[i].timer < DustEffectTime) continue;
		effects[i].timer = DustEffectTime;

		if (effects[i].dusts.IsDeath()) count++;
		if (count >= effects.size())
		{
			isDeath = true;
			effects.clear();
			return;
		}
		effects[i].dusts.Update();
	}
}

void DustEffecter::Draw(const Vector2Int& camera)
{
	if (isDeath) return;
	for (size_t i = 0; i < effects.size(); i++)
	{
		if (effects[i].timer < DustEffectTime) continue;
		effects[i].dusts.Draw(camera);
	}
}

void DustEffecter::SetLeftTop(Vector2Int* leftTop)
{
	if (leftTop == nullptr) return;
	this->leftTop = leftTop;
}
