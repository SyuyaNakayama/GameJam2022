#include "ArrowDraw.h"
#include "enum.h"
#include "function.h"

ArrowDraw::ArrowDraw() :
	pos(), scale(1.0f), rota(0.0f), direction(Up),
	ease(), timer(0), change(false),
	trans(255), shadow(0), brightness(nullptr), 
	playerPos(nullptr)
{}

void ArrowDraw::Initialize(const Vector2Int& leftTop, const Vector2Int& num, const int direction, const int arrowG[2])
{
	this->number = num;
	pos = { leftTop.x + num.x * 64, leftTop.y + num.y * 64 };
	scale = 1.0f;
	rota = 0.0f;
	ChangeDirection(direction);
	ease.Initialize(0.1f, 0.1f);
	timer = 0;
	change = false;
	trans = 255;
	for (size_t i = 0; i < 2; i++)
	{
		this->arrowG[i] = arrowG[i];
	}
}

void ArrowDraw::Update()
{
	if (!change)
	{
		if (++timer >= 20)
		{
			change = true;
			timer = 0;
		}
	}
	ease.Update(change);
	scale = ease.In(1.0f, 0.5f, 2.0f);
	trans = (int)ease.In(255.0f, 0.0f, 2.0f);

	if (ease.ratio < 1.0f) { return; }
	change = false;
	switch (direction)
	{
	case Up:
		direction = Right;
		break;
	case Down:
		direction = Left;
		break;
	case Left:
		direction = Up;
		break;
	case Right:
		direction = Down;
		break;
	}
	ChangeDirection(direction);
	UpdateShadow();
}

void ArrowDraw::ChangeDirection(const int direction)
{
	this->direction = direction;
	switch (direction)
	{
	case Up:
		rota = 0.0f;
		break;
	case Down:
		rota = DX_PI_F;
		break;
	case Left:
		rota = DX_PI_F * 1.5f;
		break;
	case Right:
		rota = DX_PI_F / 2.0f;
		break;
	}
}

void ArrowDraw::UpdateShadow()
{
	if (!playerPos || !brightness) return;

	Vector2Int disPandB = Vector2Int(*playerPos - number).absVec();

	int p = 0;
	if (disPandB.x > disPandB.y) p = disPandB.x;
	else p = disPandB.y;

	if (p > *brightness) shadow = 255;
	else shadow = 255 - ((*brightness - p) * 60);

	Clamp(shadow, 255);
}

void ArrowDraw::Draw(const Vector2Int& camera)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, trans);
	DrawRotaGraph(pos.x + camera.x, pos.y - 8 + camera.y, scale, rota, arrowG[0], true);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, shadow);
	DrawRotaGraph(pos.x + camera.x, pos.y - 8 + camera.y, scale, rota, arrowG[1], true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void ArrowDraw::SetBrightness(int* brightness)
{
	if (!brightness) return;
	this->brightness = brightness;
}

void ArrowDraw::SetPlayerPos(Vector2Int* playerPos)
{
	if (!playerPos) return;
	this->playerPos = playerPos;
}