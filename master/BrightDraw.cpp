#include "BrightDraw.h"
#include "DxLib.h"

BrightDraw::BrightDraw() :
	topL(), topR(), btmL(), btmR(),
	bright(false),
	corner1(false), finish1(false), corner2(false), finish2(false),
	trans(0), whiteG(0)
{}

void BrightDraw::Initialize(const Vector2Int& leftTop, const Vector2Int& num, const int brightM[2], const int whiteG)
{
	this->number = num;
	pos = { leftTop.x + num.x * 64, leftTop.y + num.y * 64 };
	Bright();
	bright = false;
	ease.Initialize(0.05f, 0.05f);
	trans = 0;
	for (size_t i = 0; i < 2; i++)
	{
		this->brightM[i] = brightM[i];
	}
	this->whiteG = whiteG;
}

void BrightDraw::Bright()
{
	bright = true;
	topL = { -32, 32 };
	topR = { -32, 32 };
	btmL = { -32, 32 };
	btmR = { -32, 32 };
	corner1 = false;
	finish1 = false;
	corner2 = false;
	finish2 = false;
}

void BrightDraw::Update()
{
	ease.Update(bright);
	trans = (int)ease.In(0.0f, 255.0f, 3.0f);

	if (trans >= 255)
	{
		MoveBright();
	}
}

void BrightDraw::MoveBright()
{
	int sp = 4;
	if (!finish1)
	{
		if (!corner1)
		{
			topL.y -= sp;
			topR.x += sp;
			if (topL.y <= -32)
			{
				topL.y = -32;
				topR.x = 32;
				corner1 = true;
			}
		}
		else
		{
			topL.x += sp;
			topR.y -= sp;
			if (topL.x >= 32)
			{
				topL.x = 32;
				topR.y = -32;
				finish1 = true;
			}
		}
	}

	if (!finish2 && topL.y <= 8)
	{
		if (!corner2)
		{
			btmL.y -= sp;
			btmR.x += sp;
			if (btmL.y <= -32)
			{
				btmL.y = -32;
				btmR.x = 32;
				corner2 = true;
			}
		}
		else
		{
			btmL.x += sp;
			btmR.y -= sp;
			if (btmL.x >= 32)
			{
				btmL.x = 32;
				btmR.y = -32;
				finish2 = true;
				bright = false;
			}
		}
	}
}

void BrightDraw::Draw(const Vector2Int& camera)
{
	CreateMaskScreen();
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, trans);
	DrawMask(pos.x - 32 + camera.x, pos.y - 32 + camera.y, brightM[0], DX_MASKTRANS_BLACK);
	DrawBox(
		pos.x - 32 + camera.x, pos.y - 32 + camera.y,
		pos.x + 32 + camera.x, pos.y + 32 + camera.y,
		GetColor(150, 240, 80), true
	);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	DrawMask(pos.x - 32 + camera.x, pos.y - 32 + camera.y, brightM[1], DX_MASKTRANS_BLACK);
	if (bright)
	{
		SetDrawBright(255, 255, 255);
		DrawModiGraph(
			pos.x + topL.x, pos.y + topL.y, // ç∂è„
			pos.x + topR.x, pos.y + topR.y, // âEè„
			pos.x + btmR.x, pos.y + btmR.y, // âEâ∫
			pos.x + btmL.x, pos.y + btmL.y, // ç∂â∫
			whiteG, true);
		SetDrawBright(255, 255, 255);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DeleteMaskScreen();
}
