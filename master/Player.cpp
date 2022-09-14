#include "Player.h"
#include "function.h"
#include "enum.h"
#include "Map.h"
#include <math.h>

void Player::LoadAndSet(Map* pMap)
{
	this->pMap = pMap;
	selecter.Load();
	selecter.SetMap(pMap);
	input = Input::GetInstance();
	sound = SoundManager::GetInstance();

	LoadDivGraph("Resources/Player/all_idle.png", 16, 4, 4, 64, 64, idleG);
	LoadDivGraph("Resources/Player/all_attack.png", 4, 4, 1, 64, 64, attackG);
}

void Player::Initialize(const Vector2Int& pos, const int direction)
{
	selecter.SetPlayerPos(&this->pos);
	Reset(pos, direction);
	selecter.Initialize(DESTROY_MAX, direction);
}

void Player::Reset(const Vector2Int& pos, const int direction)
{
	this->pos = pos;
	this->direction = direction;
	ActionReset();
	selecter.Reset(direction);
	move = { -1, -1 };

	mode = Mode::Select;
	next = Mode::Select;
	stopTimer = 0;

	animeT = 0;
	anime = 0;
	clash = false;
}

void Player::ActionReset()
{
	actionNum = 15;
	damageCount = 0;
}

void Player::Update()
{
	selecter.Update(mode == Mode::Select);
	Action();
	if (damageCount > 0)
	{
		actionNum -= damageCount;
		damageCount = 0;
	}
	pMap->drawer.SetBrightness(actionNum);
	if ((actionNum - damageCount) == 5) pMap->drawer.ChipBright();
}

void Player::Action()
{
	if (++animeT > 5) 
	{
		animeT = 0;
		if (++anime > 3) anime = 0;
	}
	if (pMap->IsFreeze()) return;
	Stop();
	Select();
	Destroy();
	Move();
}

void Player::Stop()
{
	if (mode != Mode::Stop) return;

	if (pMap->breakCount <= 0) mode = next;
}

void Player::Select()
{
	if (mode != Mode::Select) return;

	if (selecter.GetRouteSize() > 0)
	{
		Vector2Int b = selecter.GetRoutePos(0);
		Vector2Int a = b - pos;
		if (a.y < 0) direction = Up;
		if (a.y > 0) direction = Down;
		if (a.x < 0) direction = Left;
		if (a.x > 0) direction = Right;
	}

	if (selecter.IsDecision())
	{
		mode = Mode::Stop;
		next = Mode::Destroy;
	}
}

void Player::Destroy()
{
	if (mode != Mode::Destroy) return;

	move = selecter.GetRoutePos(0);
	pMap->BreakBlock(move);

	if (selecter.IsSelectBomb())
	{
		// îöíeÇÃÉuÉçÉbÉNîjâ˙
		for (size_t i = 0; i < pMap->GetBomb().size(); i++)
		{
			if (pMap->GetBomb()[i].GetPos() == move)
			{
				pMap->EraseBomb(i);
				pMap->BombDestroy(i, this);
			}
		}
		sound->PlaySE(0);
	}

	selecter.EraseRoute(0);
	mode = Mode::Stop;
	next = Mode::Move;
	clash = true;
}

void Player::Move()
{
	if (mode != Mode::Move) return;
	if (move.x == -1 && move.y == -1) return;

	Vector2Int a = move - pos;

	if (a.y < 0) direction = Up;
	if (a.y > 0) direction = Down;
	if (a.x < 0) direction = Left;
	if (a.x > 0) direction = Right;

	pos = move;
	Clamp(pos, pMap->GetMapSize() - Vector2Int(1, 1));
	move = { -1, -1 };

	if (selecter.GetRouteSize() >= 1)
	{
		mode = Mode::Stop;
		next = Mode::Destroy;
	}
	else
	{
		mode = Mode::Stop;
		next = Mode::Select;
		actionNum--;
		selecter.Reset(selecter.GetDirection());
	}
	clash = false;
}

void Player::Draw(const Vector2Int& camera)
{
	selecter.Draw(camera);
	Vector2Int p = { pMap->GetMapPos().x + (64 * pos.x) - 32, pMap->GetMapPos().y + (64 * pos.y) - 32 };

	if (clash) 
	{
		int d = direction;
		DrawGraph(p.x, p.y, attackG[d], true);
	}
	else
	{
		int d = direction * 4;
		DrawGraph(p.x, p.y, idleG[(d + anime)], true);
	}
}