#include "BreakBlockList.h"
#include "DxLib.h"

void BreakBlockList::Initialize()
{
	Clear();
	timer = 0;
	wait = false;
	waitTime = 0;
}

void BreakBlockList::Update()
{
	front = { -1,-1 };
	if (!wait) return;

	if (blocks[0].exposure) waitTime = ExprosionTime;
	else waitTime = MiningTime;

	if (++timer >= waitTime)
	{
		front = blocks[0].number;
		blocks.erase(std::begin(blocks));
		timer = 0;
		wait = (blocks.size() >= 1);
		waitTime = 0;
	}
}

void BreakBlockList::PushBuck(const Vector2Int& num, const bool bomb)
{
	BreakBlockPara b;
	b.number = num;
	b.exposure = bomb;
	blocks.push_back(b);
	wait = true;
	if (bomb) bombBreak++;
}

bool BreakBlockList::PopFront(Vector2Int& reciever)
{
	if (front.x != -1 && front.y != -1)
	{
		reciever = front;
		return true;
	}

	return false;
}

void BreakBlockList::Clear()
{
	blocks.clear();
	front = { -1,-1 };
}

void BreakBlockList::DrawDebug()
{
	int s = (int)blocks.size();
	DrawFormatString(300, 300, GetColor(255, 0, 0), "%d", s);
	DrawFormatString(300, 150, GetColor(255, 0, 0), "%d", timer);
}
