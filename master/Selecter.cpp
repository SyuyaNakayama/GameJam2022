#include "Selecter.h"
#include "Map.h"
#include "function.h"

void Selecter::Load()
{
	drawer.Load();
	input = Input::GetInstance();
}

void Selecter::Initialize(const int choseMax)
{
	Reset();
	drawer.Initialize(pMap->GetMapPos());
	this->choseMax = choseMax;
}

void Selecter::Reset()
{
	pos = *playerPos;
	direction = Up;
	chose.clear();
	decision = false;
	bomb = false;
}

void Selecter::Update()
{
	if (decision) return;
	DirectionUpdate();
	Move();
	ChipSelect();
	drawer.Update();
}

void Selecter::DirectionUpdate()
{
	if (input->IsUp())	  direction = Up;
	if (input->IsDown())  direction = Down;
	if (input->IsLeft())  direction = Left;
	if (input->IsRight()) direction = Right;
}

void Selecter::Move()
{
	if (chose.size() >= choseMax) return;

	Vector2Int elder;
	if (chose.size() <= 0) elder = *playerPos;
	else elder = chose.back();

	if (direction == Up)	 pos = { elder.x, elder.y - 1 };
	if (direction == Down)	 pos = { elder.x, elder.y + 1 };
	if (direction == Left)	 pos = { elder.x - 1, elder.y };
	if (direction == Right)	 pos = { elder.x + 1, elder.y };

	Clamp(pos, pMap->GetMapSize() - Vector2Int(1, 1));
}

void Selecter::ChipSelect()
{
	if (input->pad->IsTrigger(input->pad->Y) &&
		(chose.size() >= choseMax || bomb))
	{
		decision = true;
	}
	if (input->pad->IsTrigger(input->pad->B) && !bomb)
	{
		if (chose.size() >= choseMax) return;
		for (size_t i = 0; i < chose.size(); i++)
		{
			if (pos.x == chose[i].x && pos.y == chose[i].y) return;
		}

		if (pMap->GetMapState(pos) == None) return;
		bomb = (pMap->GetMapState(pos) == BombBlock);

		Vector2Int c = pos;
		chose.push_back(c);
	}
	if (input->pad->IsTrigger(input->pad->A))
	{
		for (size_t i = 0; i < chose.size(); i++)
		{
			chose.clear();
		}
		bomb = false;
	}
}

void Selecter::Draw(const Vector2Int& camera)
{
	for (size_t i = 0; i < chose.size(); i++)
	{
		drawer.ChoseDraw(chose[i], camera);
	}
	if (chose.size() >= choseMax || !bomb) drawer.Draw(pos, camera);
}

void Selecter::SetPlayerPos(Vector2Int* playerPos)
{
	if (playerPos == nullptr) return;
	this->playerPos = playerPos;
}

void Selecter::SetMap(Map* map)
{
	if (map == nullptr) return;
	this->pMap = map;
}

Vector2Int Selecter::GetRoutePos(const int num)
{
	if (num <= 0 || chose.size() - 1 <= num) return Vector2Int(-1, -1);
	return chose[num];
}

Vector2Int Selecter::GetRouteBack()
{
	if (chose.size() <= 0) return Vector2Int(-1, -1);
	return chose.back();
}

void Selecter::EraseRoute(const int num)
{
	if (num <= 0 || chose.size() - 1 <= num) return;
	chose.erase(std::begin(chose) + num);
}

