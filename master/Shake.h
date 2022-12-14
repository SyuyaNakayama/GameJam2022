#pragma once
#include "Vector2.h"

class Shake 
{
private:
	Vector2Int value{};			// 実数値
	bool isShake = false;	// 揺れているか
	int swingValue = 0;	// 揺れる量 (乱数)
	int dekey = 0;		// 減衰量
public:
	void Initialize();
	void Update();
	void Shaking(const int swing, const int dekey);
	Vector2Int GetValue() { return value; }
	bool IsShake() { return isShake; }
	float Ratio() { return 1.0f - dekey / swingValue; }
};