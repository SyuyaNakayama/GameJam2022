#include "Keys.h"
#include "enum.h"

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
	LoadDivGraph("Resources/UI/key_UP.png", 2, 2, 1, 64, 64, directionKeyG[Up]);
	LoadDivGraph("Resources/UI/key_DOWN.png", 2, 2, 1, 64, 64, directionKeyG[Down]);
	LoadDivGraph("Resources/UI/key_LEFT.png", 2, 2, 1, 64, 64, directionKeyG[Left]);
	LoadDivGraph("Resources/UI/key_RIGHT.png", 2, 2, 1, 64, 64, directionKeyG[Right]);

	LoadDivGraph("Resources/UI/key.png", 2, 2, 1, 64, 64, keyG);

	LoadDivGraph("Resources/UI/key_SPACE.png", 2, 2, 1, 128, 64, spaceKeyG);
	LoadDivGraph("Resources/UI/key_SHIFT.png", 2, 2, 1, 96, 64, shiftKeyG);
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

	downArrow[Up] = IsDown(KEY_INPUT_UP);
	downArrow[Down] = IsDown(KEY_INPUT_DOWN);
	downArrow[Left] = IsDown(KEY_INPUT_LEFT);
	downArrow[Right] = IsDown(KEY_INPUT_RIGHT);

	downShift = IsDown(KEY_INPUT_LSHIFT) || IsDown(KEY_INPUT_RSHIFT);
	downSpace = IsDown(KEY_INPUT_SPACE);
	downS = IsDown(KEY_INPUT_S);
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

void Keys::DrawArrow(const Vector2Int& pos)
{
	DrawUp({ pos.x + 64, pos.y });
	DrawDown({ pos.x + 64, pos.y + 96 });
	DrawLeft({ pos.x, pos.y + 48 });
	DrawRight({ pos.x + 128, pos.y + 48 });
}
void Keys::DrawUp(const Vector2Int& pos)
{
	DrawGraph(pos.x, pos.y, directionKeyG[Up][downArrow[Up]], true);
}
void Keys::DrawDown(const Vector2Int& pos)
{
	DrawGraph(pos.x, pos.y, directionKeyG[Down][downArrow[Down]], true);
}
void Keys::DrawLeft(const Vector2Int& pos)
{
	DrawGraph(pos.x, pos.y, directionKeyG[Left][downArrow[Left]], true);
}
void Keys::DrawRight(const Vector2Int& pos)
{
	DrawGraph(pos.x, pos.y, directionKeyG[Right][downArrow[Right]], true);
}

void Keys::DrawKey(const Vector2Int& pos)
{
	DrawGraph(pos.x, pos.y, keyG[downS], true);
}

void Keys::DrawShift(const Vector2Int& pos)
{
	DrawGraph(pos.x, pos.y, shiftKeyG[downShift], true);
}
void Keys::DrawSpace(const Vector2Int& pos)
{
	DrawGraph(pos.x, pos.y, spaceKeyG[downSpace], true);
}
