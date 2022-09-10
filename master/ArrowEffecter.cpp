#include "ArrowEffecter.h"
#include "enum.h"
#include "DrawParameter.h"

void ArrowEffecter::Load()
{
	LoadDivGraph("Resources/Block/arrow.png", 2, 2, 1, 32, 32, arrowG);
}

void ArrowEffecter::Emit(const Vector2Int& num, const int direction, int* brightness, Vector2Int* playerPos)
{
	if (!leftTop) return;
	ArrowEffect effect;
	effect.arrow.Initialize(*leftTop, num, direction, arrowG);
	effect.timer = 0;
	effect.arrow.SetBrightness(brightness);
	effect.arrow.SetPlayerPos(playerPos);
	effects.push_back(effect);
	isDeath = false;
}

void ArrowEffecter::Erase(const Vector2Int& num)
{
	for (size_t i = 0; i < effects.size(); i++)
	{
		if (effects[i].arrow.GetNumber().x == num.x && 
			effects[i].arrow.GetNumber().y == num.y)
		{
			effects.erase(std::begin(effects) + i);
		}
	}
}

void ArrowEffecter::Crear()
{
	effects.clear();
}

void ArrowEffecter::Update()
{
	for (size_t i = 0; i < effects.size(); i++)
	{
		if (++effects[i].timer >= ArrowEffectTime) effects[i].timer = ArrowEffectTime;
		effects[i].arrow.Update();
	}
}

void ArrowEffecter::Draw(const Vector2Int& camera)
{
	for (size_t i = 0; i < effects.size(); i++)
	{
		if (effects[i].timer < ArrowEffectTime) continue;
		effects[i].arrow.Draw(camera);
	}
}

void ArrowEffecter::SetLeftTop(Vector2Int* leftTop)
{
	if (leftTop == nullptr) return;
	this->leftTop = leftTop;
}
