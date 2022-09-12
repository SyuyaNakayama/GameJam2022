#include "Bomb.h"
#include "enum.h"

void Bomb::Initialize(const Vector2Int& pos, const int direction)
{
	this->pos = pos;
	switch (direction)
	{
	case 0:	this->direction = Up;    break;
	case 1:	this->direction = Down;  break;
	case 2:	this->direction = Left;  break;
	case 3:	this->direction = Right; break;
	}
}

void Bomb::Rotate()
{
	if (++timer <= RotaTimer) return;
	timer = 0;

	switch (direction)
	{
	case Up:	direction = Right;	break;
	case Down:	direction = Left;	break;
	case Left:	direction = Up;		break;
	case Right:	direction = Down;	break;
	}
}

std::vector<Vector2Int> Bomb::Explosion()
{
	std::vector<Vector2Int>destroyPos;
	switch (direction)
	{
	case Up:
		for (int y = 0; y < 5 && pos.y - y - 1 >= 0; y++)
		{
			destroyPos.push_back(pos - Vector2Int(0, y + 1));
		}
		break;
	case Down:
		for (int y = 0; y < 5 && pos.y + y + 1 <= 9; y++)
		{
			destroyPos.push_back(pos + Vector2Int(0, y + 1));
		}
		break;
	case Left:
		for (int x = 0; x < 5 && pos.x - x - 1 >= 0; x++)
		{
			destroyPos.push_back(pos - Vector2Int(x + 1, 0));
		}
		break;
	case Right:
		for (int x = 0; x < 5 && pos.x + x + 1 <= 9; x++)
		{
			destroyPos.push_back(pos + Vector2Int(x + 1, 0));
		}
		break;
	}
	isExplosion = 1;
	return destroyPos;
}
