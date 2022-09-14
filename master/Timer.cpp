#include "Timer.h"
#include "DxLib.h"
#include "function.h"

bool Timer::CountDown(int playerDamageCount)
{
	time = GetNowCount() - start + playerDamageCount * 10000;

	time = limit - time;
	s = (time % limit) / 1000;
	cs = (time % 1000) / 10;

	return time <= 0;
}

void Timer::Draw(Vector2Int pos)
{
	if (time > 0)
	{
		DrawFormatString(pos.x, pos.y, GetColor(255, 255, 255), ":%02d.%02d", s, cs);
	}
	else
	{
		DrawFormatString(pos.x, pos.y, GetColor(255, 255, 255), ":00:00");
	}
}

void Timer::Reset()
{
	*this = Timer(GetNowCount(), maxTime);
}
