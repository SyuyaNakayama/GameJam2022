#pragma once
#include "Vector2.h"

class Shake 
{
private:
	Vector2Int value{};			// À”’l
	bool isShake = false;	// —h‚ê‚Ä‚¢‚é‚©
	float swingValue = 0;	// —h‚ê‚é—Ê (—”)
	float dekey = 0;		// Œ¸Š—Ê
public:
	void Initialize();
	void Update();
	void Shaking(const float swing, const float dekey);
	Vector2Int GetValue() { return value; }
	bool IsShake() { return isShake; }
	float Ratio() { return 1.0f - dekey / swingValue; }
};