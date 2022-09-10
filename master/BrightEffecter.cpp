#include "BrightEffecter.h"
#include "DxLib.h"
#include "DrawParameter.h"

void BrightEffecter::Load()
{
	LoadDivMask("Resources/Block/ore_mask.png", 2, 2, 1, 64, 64, brightM);
	whiteG = LoadGraph("Resources/Block/white.png");
}

void BrightEffecter::Emit(const Vector2Int& num)
{
	if (!leftTop) return;
	BrightEffect effect;
	effect.bright.Initialize(*leftTop, num, brightM, whiteG);
	effect.timer = 0;
	effects.push_back(effect);
	isDeath = false;
}

void BrightEffecter::Erase(const Vector2Int& num)
{
	for (size_t i = 0; i < effects.size(); i++)
	{
		if (effects[i].bright.GetNumber().x == num.x &&
			effects[i].bright.GetNumber().y == num.y)
		{
			effects.erase(std::begin(effects) + i);
		}
	}
}

void BrightEffecter::Crear()
{
	effects.clear();
}

void BrightEffecter::Update()
{
	if (isDeath) return;
	if (bright)
	{
		if (++timer >= 120)
		{
			Bright();
			timer = 0;
		}
	}

	for (size_t i = 0; i < effects.size(); i++)
	{
		if (++effects[i].timer >= BrightStartTime) effects[i].timer = BrightStartTime;
		effects[i].bright.Update();
	}
	isDeath = (effects.size() <= 0);
}

void BrightEffecter::Bright()
{
	if (isDeath) return;
	bright = true;
	for (size_t i = 0; i < effects.size(); i++)
	{
		if (effects[i].timer < BrightStartTime) continue;
		effects[i].bright.Bright();
	}
}

void BrightEffecter::Draw(const Vector2Int& camera)
{
	if (isDeath) return;
	for (size_t i = 0; i < effects.size(); i++)
	{
		if (effects[i].timer < BrightStartTime) continue;
		effects[i].bright.Draw(camera);
	}
}

void BrightEffecter::SetLeftTop(Vector2Int* leftTop)
{
	if (leftTop == nullptr) return;
	this->leftTop = leftTop;
}
