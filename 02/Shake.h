#pragma once
#include "Vector2.h"

class Shake 
{
private:
	Vector2Int value{};			// 実数値
	bool isShake = false;	// 揺れているか
	float swingValue = 0;	// 揺れる量 (乱数)
	float dekey = 0;		// 減衰量
public:
	void Initialize();
	void Update();
	void Shaking(const float swing, const float dekey);
	Vector2Int GetValue() { return value; }
	bool IsShake() { return isShake; }
	float Ratio() { return 1.0f - dekey / swingValue; }
};