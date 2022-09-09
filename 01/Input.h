#pragma once

class Input
{
private:
	char key[256]{}, oldkey[256]{};
public:
	void Update();
	bool IsInput(const int KEY_NUM);
	bool IsTrigger(const int KEY_NUM);
	bool IsTriggerMoveKey();
};