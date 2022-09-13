#include "CrystalEffecter.h"
#include "DxLib.h"

void CrystalEffecter::Load()
{
	LoadDivGraph("Resources/crystal.png", 1, 1, 2, 64, 64, &crystalG);
}

void CrystalEffecter::Emit(const Vector2Int& num)
{
	if (!leftTop) return;
	CrystalEffect c;
	c.pos = { leftTop->x + (num.x * 64), leftTop->y + (num.y * 64) };
	c.height = 0;
	c.ease.Initialize(0.1f);
	effects.push_back(c);
}

void CrystalEffecter::Clear()
{
	effects.clear();
}

void CrystalEffecter::Update()
{
	if (effects.empty()) return;

	for (size_t i = 0; i < effects.size(); i++)
	{
		effects[i].ease.Update(true);

		if (!effects[i].jet && effects[i].trans >= 200)
		{
			effects[i].jet = true;
			effects[i].ease.Initialize(0.1f);
		}

		if (effects[i].jet && effects[i].trans <= 0)
		{
			Erase(i);
			continue;
		}

		if (effects[i].jet)
		{
			effects[i].height = (int)effects[i].ease.In(-96.0f, -192.0f, 2.0f);
			effects[i].trans = (int)effects[i].ease.In(200.0f, 0.0f, 2.0f);
		}
		else
		{
			effects[i].height = (int)effects[i].ease.In(0.0f, -96.0f, 2.0f);
			effects[i].trans = (int)effects[i].ease.In(0.0f, 200.0f, 2.0f);
		}
	}
}

void CrystalEffecter::Erase(const int num)
{
	effects.erase(std::begin(effects) + num);
}

void CrystalEffecter::Draw(const Vector2Int& camera)
{
	for (size_t i = 0; i < effects.size(); i++)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, effects[i].trans);
		DrawRotaGraph(
			effects[i].pos.x + camera.x,
			effects[i].pos.y + effects[i].height + camera.y,
			0.75f, 0.0f,
			crystalG, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

void CrystalEffecter::SetLeftTop(Vector2Int* leftTop)
{
	if (leftTop == nullptr) return;
	this->leftTop = leftTop;
}
