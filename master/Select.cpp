#include "Select.h"
#include "Map.h"

void Select::Load()
{
	drawer.Load();
}

void Select::Initialize(const int choseMax)
{
	pos = *playerPos;
	direction = -1;
	drawer.Initialize(pMap->GetMapPos());
	this->choseMax = choseMax;
}

void Select::Update()
{
	DirectionUpdate();
	Move();
	ChipSelect();
	drawer.Update();
}

void Select::DirectionUpdate()
{
	direction = -1;
	if (true) direction = Up;
	if (true) direction = Down;
	if (true) direction = Left;
	if (true) direction = Right;
}

void Select::Move()
{
	Vector2Int elder, current;
	if (chose.size() <= 0) elder = *playerPos;
	else elder = chose.back();
	current = pos;

	if (direction == Up)    current.y--;
	if (direction == Down)  current.y++;
	if (direction == Left)  current.x--;
	if (direction == Right) current.x++;

	Vector2 v = { (float)(current.x - elder.x), (float)(current.y - elder.y) };
	if (v.length() > 1.1f) return;

	pos = current;
}

void Select::ChipSelect()
{
	if (true)
	{
		if (chose.size() >= choseMax) return;
		for (size_t i = 0; i < chose.size(); i++)
		{
			if (pos.x == chose[i].x && pos.y == chose[i].y) return;
		}

		if (pMap->GetMapState(pos) == None) return;

		Vector2Int c = pos;
		chose.push_back(c);
	}
	if (true)
	{
		for (size_t i = 0; i < chose.size(); i++)
		{
			chose.clear();
		}
	}
}

void Select::Draw(const Vector2Int& camera)
{
	for (size_t i = 0; i < chose.size(); i++)
	{
		drawer.ChoseDraw(chose[i], camera);
		drawer.Draw(pos, camera);
	}
}

void Select::SetPlayerPos(Vector2Int* playerPos)
{
	if (playerPos == nullptr) return;
	this->playerPos = playerPos;
}

void Select::SetMap(Map* map)
{
	if (map == nullptr) return;
	this->pMap = map;
}

