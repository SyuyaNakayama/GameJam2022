#pragma once
#include "Vector2.h"

class Shake 
{
private:
	Vector2Int value{};			// À”’l
	bool isShake = false;	// —h‚ê‚Ä‚¢‚é‚©
	int swingValue = 0;	// —h‚ê‚é—Ê (—”)
	int dekey = 0;		// Œ¸Š—Ê
public:
	void Initialize();
	void Update();
	void Shaking(const int swing, const int dekey);
	Vector2Int GetValue() { return value; }
	bool IsShake() { return isShake; }
	float Ratio() { return 1.0f - dekey / swingValue; }
};