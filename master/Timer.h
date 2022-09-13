#pragma once
#include "Vector2.h"
class Timer
{
private:
	int start, limit, time, s, cs,maxTime;
public:
	Timer(int s_time, int l_time) { start = s_time; limit = l_time * 1000; time = s = cs = 0; maxTime = l_time; }
	bool CountDown(int playerDamageCount);
	void Draw(Vector2Int);
	void Reset();
};