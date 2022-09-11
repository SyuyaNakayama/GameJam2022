#include "Select.h"
#include "enum.h"

void Select::Load()
{
	setG = LoadGraph("Resources/frame.png");
}

void Select::Initialize(const Vector2Int& playerPos)
{

}

void Select::Update()
{

}

void Select::Draw(const Vector2Int& camera)
{
	if (!leftTop) return;
	//DrawRotaGraph();
	//DrawRotaGraph();
	//DrawRotaGraph();
	//DrawRotaGraph();
}

void Select::SetLeftTop(Vector2Int* leftTop)
{
	if (leftTop == nullptr) return;
	this->leftTop = leftTop;
}
