#include "Ease.h"
#include <math.h>

float lerp(const float a, const float b, const float t)
{
	return a + t * (b - a);
}
float EaseIn(const float start, const float end, const float time, const float power)
{
	return lerp(start, end, pow(time, power));
}
float EaseOut(const float start, const float end, const float time, const float power)
{
	return lerp(start, end, 1 - pow(1 - time, power));
}

Ease::Ease() :
	ratio(0.0f), increase(0.0f)
{}

Ease::Ease(const float increase) :
	ratio(0.0f), increase(increase)
{}

void Ease::Initialize(const float increase)
{
	this->ratio = 0.0f;
	this->increase = increase;
}

void Ease::Update(const bool isEase)
{
	if (isEase)
	{
		ratio += increase;
		if (ratio >= 1.0f) ratio = 1.0f;
	}
}

float Ease::In(const float start, const float end, const float power)
{
	return EaseIn(start, end, ratio, power);
}

float Ease::Out(const float start, const float end, const float power)
{
	return EaseOut(start, end, ratio, power);
}

Ease2::Ease2() : 
	decrease(0)
{}

Ease2::Ease2(const float increase, const float decrease)
{
	this->ratio = 0.0f;
	this->increase = increase;
	this->decrease = decrease;
}

void Ease2::Initialize(const float increase, const float decrease)
{
	this->ratio = 0.0f;
	this->increase = increase;
	this->decrease = decrease;
}

void Ease2::Update(const bool isEase)
{
	if (isEase)
	{
		ratio += increase;
		if (ratio >= 1.0f) ratio = 1.0f;
	}
	else
	{
		ratio -= decrease;
		if (ratio <= 0.0f) ratio = 0.0f;
	}
}
