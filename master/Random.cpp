#include "Random.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <compare>

void InitRand() { srand((int)time(NULL)); }

int GetRand(const int start, const int end)
{
	int div = end - start;
	if (div > 0) div++;
	if (div < 0) div--;
	if (div == 0) return end;

	return ((rand() % div) + start);
}

float GetRandF(const float start, const float end)
{
	float div = end - start;
	if (div > 0.0f) div += 1.0f;
	if (div < 0.0f) div -= 1.0f;
	if (div == 0.0f) return end;

	return (fmodf((float)rand(), div) + start);
}
