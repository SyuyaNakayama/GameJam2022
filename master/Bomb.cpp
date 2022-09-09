#include "Bomb.h"

Bomb::Bomb(Vector2Int pos_, int dir)
{
	pos = pos_; 
	switch (dir)
	{
	case 0:	direction = Up;    break;
	case 1:	direction = Down;  break;
	case 2:	direction = Left;  break;
	case 3:	direction = Right; break;
	}
}

void Bomb::Rotate()
{
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
	return destroyPos;
}
