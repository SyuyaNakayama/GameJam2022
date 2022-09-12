#include "SelectDraw.h"
#include "DxLib.h"

void SelectDraw::Load()
{
	setG = LoadGraph("Resources/frame.png");
}

void SelectDraw::Initialize(const Vector2Int& leftTop)
{
	this->leftTop = leftTop;
}

void SelectDraw::Update()
{
}

void SelectDraw::ChoseDraw(const Vector2Int& pos, const Vector2Int& camera)
{
	Vector2Int center = { leftTop.x + pos.x * 64, leftTop.y + pos.y * 64 };
	SetCompDraw(center);
}

void SelectDraw::SetCompDraw(const Vector2Int& center)
{
	DrawCircle(center.x, center.y, 24, GetColor(255, 0, 0), false);
	//DrawRotaGraph(center.x, center.y);
	//DrawRotaGraph(center.x, center.y);
	//DrawRotaGraph(center.x, center.y);
	//DrawRotaGraph(center.x, center.y);
}

void SelectDraw::Draw(const Vector2Int& pos, const Vector2Int& camera)
{
	Vector2Int center = { leftTop.x + pos.x * 64, leftTop.y + pos.y * 64 };
	SetDraw(center);
}

void SelectDraw::SetDraw(const Vector2Int& center)
{
	DrawCircle(center.x, center.y, 32, GetColor(255, 255, 255), false);
	//DrawRotaGraph(center.x, center.y);
	//DrawRotaGraph(center.x, center.y);
	//DrawRotaGraph(center.x, center.y);
	//DrawRotaGraph(center.x, center.y);
}
