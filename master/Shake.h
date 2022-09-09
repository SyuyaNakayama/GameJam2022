#pragma once
#include "Vector2.h"

class Shake 
{
private:
	Vector2Int value{};			// �����l
	bool isShake = false;	// �h��Ă��邩
	int swingValue = 0;	// �h���� (����)
	int dekey = 0;		// ������
public:
	void Initialize();
	void Update();
	void Shaking(const int swing, const int dekey);
	Vector2Int GetValue() { return value; }
	bool IsShake() { return isShake; }
	float Ratio() { return 1.0f - dekey / swingValue; }
};