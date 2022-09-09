#include "Shake.h"
#include "Random.h"

void Shake::Initialize()
{
	value = {};
	isShake = false;
	swingValue = 0;
	dekey = 0;
}

void Shake::Shaking(const int swing, const int dekey)
{
	value = {};
	isShake = true;
	this->dekey = dekey;
	swingValue = swing;
}

void Shake::Update() {
	// ”ÍˆÍ‚ğ‹·‚ß‚é
	if (swingValue > 0) {
		swingValue -= dekey;
	}

	// ”ÍˆÍ“à‚Ì—”¶¬
	if (isShake) {
		value.x = GetRand(-swingValue, swingValue);
		value.y = GetRand(-swingValue, swingValue);
	}

	if (swingValue <= 0) {
		value = { 0, 0 };
		swingValue = 0;
		isShake = false;
	}
}