#include "ArrowDraw.h"
#include "DxLib.h"
#include "enum.h"

ArrowDraw::ArrowDraw() :
	scale(1.0f), rota(0.0f), direction(Up), 
	ease(), timer(0), change(false),
	trans(255), arrowG(0)
{}

void ArrowDraw::Initialize(const int direction, const int arrowG)
{
	scale = 1.0f;
	rota = 0.0f;
	ChangeDirection(direction);
	ease.Initialize(0.1f, 0.1f);
	timer = 0;
	change = false;
	trans = 255;
	this->arrowG = arrowG;
}

void ArrowDraw::Update()
{
	if (!change) timer++;
	if (timer >= 20)
	{
		change = true;
		timer = 0;
	}
	ease.Update(change);
	scale = ease.In(1.0f, 0.5f, 2.0f);
	trans = (int)ease.In(255.0f, 0.0f, 2.0f);

	if (ease.ratio >= 1.0f)
	{
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
		default:
			break;
		}
		ChangeDirection(direction);
	}
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
		rota = 3.141592f;
		break;
	case Left:
		rota = 3.141592f * 1.5f;
		break;
	case Right:
		rota = 3.141592f / 2.0f;
		break;
	default:
		break;
	}
}

void ArrowDraw::Draw(const Vector2Int& pos, const Vector2Int& camera, const int trans)
{
	int t = this->trans;
	if (trans < 255) t = trans;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, t);
	DrawRotaGraph(pos.x + camera.x, pos.y - 8 + camera.y, scale, rota, arrowG, true);
}
