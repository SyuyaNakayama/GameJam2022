#include "Random.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>

void InitRand() { srand(time(NULL)); }

int GetRand(const int start, const int end) 
{
	return ((rand() % (end + 1)) + start);
}

float GetRandF(const float start, const float end) 
{
	return (fmodf(rand(), (end + 1.0f)) + start);
}
