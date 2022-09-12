#pragma once

class Keys
{
private:
	char* keys;
	char* oldkeys;
public:
	void Load();
	void Update();
	bool IsDown(const int key);
	bool IsTrigger(const int key);
	bool IsLongPress(const int key);
	bool IsRelease(const int key);
	int Horizontal();
	int Vertical();
public:
	static Keys* GetInstance();
private:
	Keys();
	~Keys();
	Keys(const Keys&) = delete;
	const Keys& operator=(const Keys&) = delete;
};

