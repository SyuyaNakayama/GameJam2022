#pragma once

float lerp(const float a, const float b, const float t);
float EaseIn(const float start, const float end, const float time, const float power);
float EaseOut(const float start, const float end, const float time, const float power);

class Ease
{
public:
	float ratio;
protected:
	float increase;
public:
	Ease();
	Ease(const float increase);
	void Initialize(const float increase);
	virtual void Update(const bool isEase);
	float In(const float start, const float end, const float power);
	float Out(const float start, const float end, const float power);
};

class Ease2 : public Ease
{
private:
	float decrease;
public:
	Ease2();
	Ease2(const float increase, const float decrease);
	void Initialize(const float increase, const float decrease);
	void Update(const bool isEase) override;
};