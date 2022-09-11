#include "BreakBlockList.h"
#include "DxLib.h"

void BreakBlockList::Initialize()
{
	Reset();
	bombBreak = 0;
}

void BreakBlockList::Reset()
{
	Clear();
	for (size_t i = 0; i < 2; i++)
	{
		timer[i] = 0;
		wait[i] = false;
	}
}

void BreakBlockList::Update()
{
	for (size_t i = 0; i < 2; i++)
	{
		front[i] = { -1,-1 };
		if (!wait[i]) continue;

		int waitTime = 0;
		if (i) waitTime = MiningTime;
		else waitTime = ExprosionTime;

		if (++timer[i] >= waitTime)
		{
			front[i] = blocks[i][0];
			blocks[i].erase(std::begin(blocks[i]));
			timer[i] = 0;
			wait[i] = (blocks[i].size() >= 1);
		}
	}
}

void BreakBlockList::PushBuck(const Vector2Int& num, const bool bomb)
{
	Vector2Int b = num;
	blocks[bomb].push_back(b);
	timer[bomb] = 0;
	wait[bomb] = true;
	if (bomb) bombBreak++;
}

bool BreakBlockList::PopBroken(Vector2Int& reciever)
{
	if (front[0].x != -1 && front[0].y != -1)
	{
		reciever = front[0];
		return true;
	}

	return false;
}

bool BreakBlockList::PopExposure(Vector2Int& reciever)
{
	if (front[1].x != -1 && front[1].y != -1)
	{
		reciever = front[1];
		return true;
	}

	return false;
}

void BreakBlockList::Clear()
{
	for (size_t i = 0; i < 2; i++)
	{
		blocks[i].clear();
		front[i] = {-1,-1};
	}
}

void BreakBlockList::DrawDebug()
{
	int s = (int)blocks[0].size();
	DrawFormatString(300, 300, GetColor(255, 0, 0), "%d", s);
	DrawFormatString(300, 150, GetColor(255, 0, 0), "%d", timer[0]);
}
