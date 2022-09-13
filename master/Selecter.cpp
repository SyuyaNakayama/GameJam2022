#include "Selecter.h"
#include "Map.h"
#include "function.h"

void Selecter::Load()
{
	drawer.Load();
	input = Input::GetInstance();
}

void Selecter::Initialize(const int choseMax, const int direction)
{
	Reset(direction);
	drawer.Initialize(pMap->GetMapPos());
	this->choseMax = choseMax;
}

void Selecter::Reset(const int direction)
{
	pos = *playerPos;
	this->direction = direction;
	chose.clear();
	decision = false;
	bomb = false;
	drawer.Reset();
}

void Selecter::Update()
{
	SummaryUpdate();
	drawer.Update();
}

void Selecter::SummaryUpdate()
{
	if (decision) return;
	DirectionUpdate();
	Move();
	ChipSelect();
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
	if (input->IsDone() && chose.size() >= 1)
	{
		decision = true;
		drawer.ClearChose();
	}
	else if (input->IsSelect() && !bomb)
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
		drawer.CreateChose(c, chose.size());
	}
	else if (input->IsCancel())
	{
		drawer.ClearChose();
		chose.clear();
		bomb = false;
	}
}

void Selecter::Draw(const Vector2Int& camera)
{
	drawer.ChoseDraw(camera);
	if (chose.size() < choseMax && !bomb) drawer.Draw(pos, camera);

	//int a = chose.size();
	//DrawFormatString(100, 400, GetColor(0, 255, 255), "%d", a);
	//DrawFormatString(100, 500, GetColor(0, 255, 255), "%d", decision);
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
	if (num < 0 || chose.size() - 1 < num) return Vector2Int(-1, -1);
	return chose[num];
}

Vector2Int Selecter::GetRouteBack()
{
	if (chose.size() <= 0) return Vector2Int(-1, -1);
	return chose.back();
}

void Selecter::EraseRoute(const int num)
{
	if (num < 0 || chose.size() - 1 < num) return;
	chose.erase(std::begin(chose) + num);
}

