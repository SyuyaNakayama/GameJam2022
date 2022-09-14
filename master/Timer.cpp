#include "Timer.h"
#include "DxLib.h"
#include "function.h"
#include "enum.h"

bool Timer::CountDown(int playerDamageCount)
{
	time = GetNowCount() - start + playerDamageCount * 10000;

	time = limit - time;
	s = (time % limit) / 1000;
	cs = (time % 1000) / 10;

	return time <= 0;
}

void Timer::Draw(Vector2Int pos, Font& font)
{
	Color color;
	if (time > 0)
	{
		DrawFormatStringToHandle(pos.x, pos.y, color.White, font.Use(FontSize::M), "ÅF%02d.%02d", s, cs);
	}
	else
	{
		DrawStringToHandle(pos.x, pos.y, "ÅF00.00", color.White, font.Use(FontSize::M));
	}
}

void Timer::Reset()
{
	*this = Timer(GetNowCount(), maxTime);
}
