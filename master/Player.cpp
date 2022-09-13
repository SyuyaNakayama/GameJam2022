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
	mode = Mode::Select;
	next = Mode::Select;
	this->direction = direction;
	selecter.Reset(direction);
	move = { -1, -1 };
	stopTimer = 0;
	ActionReset();
}

void Player::ActionReset()
{
	damageCount = 0;
	actionNum = 15;
}

void Player::Update()
{
	selecter.Update();
	Stop();
	Select();
	Destroy();
	Move();
	if (damageCount > 0)
	{
		actionNum -= damageCount;
		damageCount = 0;
	}
	pMap->drawer.SetBrightness(actionNum);
	if ((actionNum - damageCount) == 5) pMap->drawer.ChipBright();
}

void Player::Stop()
{
	if (mode != Mode::Stop) return;

	if (pMap->breakCount <= 0) mode = next;
}

void Player::Select()
{
	if (mode != Mode::Select) return;

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
	pMap->breakCount++;
	pMap->bbList.PushBuck(move);

	if (selecter.IsSelectBomb())
	{
		// ”š’e‚ÌƒuƒƒbƒN”j‰ú
		for (size_t i = 0; i < pMap->GetBomb().size(); i++)
		{
			if (pMap->GetBomb()[i].GetPos() == move)
			{
				pMap->EraseBomb(i);
				pMap->BombDestroy(i, this);
			}
		}
	}

	selecter.EraseRoute(0);
	mode = Mode::Stop;
	next = Mode::Move;
}

void Player::Move()
{
	if (mode != Mode::Move) return;
	if (move.x == -1 && move.y == -1) return;

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
}

void Player::Draw(const Vector2Int& camera)
{
	selecter.Draw(camera);
	Color color;
	DrawCircle(pMap->GetChipPos(pos).x, pMap->GetChipPos(pos).y, 32, color.Cyan);
	DrawDebugNumber(damageCount, 96);
}