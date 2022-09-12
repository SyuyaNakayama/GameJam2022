#include "Keys.h"
#include "DxLib.h"

Keys* Keys::GetInstance()
{
	static Keys instance;
	return &instance;
}

Keys::Keys() :
	keys(new char[256]), oldkeys(new char[256])
{
	for (int i = 0; i < 256; i++)
	{
		keys[i] = 0;
		oldkeys[i] = 0;
	}
}

Keys::~Keys()
{
	delete keys;
	keys = 0;
	delete oldkeys;
	oldkeys = 0;
}

void Keys::Load()
{
}

void Keys::Update()
{
	// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
	for (int i = 0; i < 256; i++)
	{
		oldkeys[i] = keys[i];
	}
	// 最新のキーボード情報を取得
	GetHitKeyStateAll(keys);
}

bool Keys::IsDown(const int key)
{
	return keys[key];
}
bool Keys::IsTrigger(const int key)
{
	return (keys[key] && !oldkeys[key]);
}
bool Keys::IsLongPress(const int key)
{
	return (keys[key] && oldkeys[key]);
}
bool Keys::IsRelease(const int key)
{
	return (!keys[key] && oldkeys[key]);
}
int Keys::Horizontal()
{
	bool right = keys[KEY_INPUT_RIGHT] || keys[KEY_INPUT_D];
	bool left = keys[KEY_INPUT_LEFT] || keys[KEY_INPUT_A];
	return right - left;
}
int Keys::Vertical()
{
	bool up = keys[KEY_INPUT_UP] || keys[KEY_INPUT_W];
	bool down = keys[KEY_INPUT_DOWN] || keys[KEY_INPUT_S];
	return down - up;
}
