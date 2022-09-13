#include "BreakEffecter.h"
#include "enum.h"
#include "DrawParameter.h"

void BreakEffecter::Load()
{
	LoadDivGraph("Resources/Block/debri.png", 2, 2, 1, 8, 8, debriG);
}

void BreakEffecter::Initialize()
{
	effects.clear();
	isDeath = false;
}

void BreakEffecter::Emit(const Vector2Int& num, const int blockName)
{
	if (!leftTop) return;
	BreakEffect effect;
	Vector2Int p = { leftTop->x + num.x * 64, leftTop->y + num.y * 64 };
	Particle::Color c[2]{};
	int g = 0;
	switch (blockName)
	{
	case Block:
		c[0] = { 150,210,220 };
		c[1] = { 100,110,140 };
		g = debriG[0];
		break;
	case CoinBlock:
		c[0] = { 250,250,100 };
		c[1] = { 130,130,90 };
		g = debriG[1];
		break;
	case CrystalBlock:
		c[0] = { 180,250,100 };
		c[1] = { 70,80,110 };
		g = debriG[1];
		break;
	case BombBlock:
		c[0] = { 240,170,20 };
		c[1] = { 160,70,40 };
		g = debriG[0];
		break;
	case None:
		break;
	}
	effect.debris.Emit({ p.x - 32, p.y - 32 }, { p.x + 32, p.y + 32 }, 20, c, g);
	effect.timer = 0;
	effects.push_back(effect);
	isDeath = false;
}

void BreakEffecter::Update()
{
	if (isDeath) return;
	size_t count = 0;
	for (size_t i = 0; i < effects.size(); i++)
	{
		if (++effects[i].timer < BreakStartTime) continue;
		effects[i].timer = BreakStartTime;

		if (effects[i].debris.IsDeath()) count++;
		if (count >= effects.size())
		{
			isDeath = true;
			effects.clear();
			return;
		}
		effects[i].debris.Update();
	}
}

void BreakEffecter::Draw(const Vector2Int& camera)
{
	if (isDeath) return;
	for (size_t i = 0; i < effects.size(); i++)
	{
		if (effects[i].timer < BreakStartTime) continue;
		effects[i].debris.Draw(camera);
	}
}

void BreakEffecter::SetLeftTop(Vector2Int* leftTop)
{
	if (leftTop == nullptr) return;
	this->leftTop = leftTop;
}
