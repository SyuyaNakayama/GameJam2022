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

void Player::Initialize(const Vector2Int& pos)
{
	selecter.SetPlayerPos(&this->pos);
	Reset(pos);
	selecter.Initialize(DESTROY_MAX);
}

void Player::Reset(const Vector2Int& pos)
{
	this->pos = pos;
	mode = Mode::Select;
	direction = Up;
	selecter.Reset();
	move = { -1, -1 };
	stopTimer = 0;
	ActionReset();
}

void Player::ActionReset()
{
	damageCount = 0;
	actionNum = 20;
}

void Player::Update()
{
	selecter.Update();
	if (selecter.IsDecision()) mode = Mode::Destroy;
	Destroy();
	Move();
	if (damageCount > 0)
	{
		actionNum - damageCount;
		damageCount = 0;
	}
	pMap->drawer.SetBrightness(actionNum);
	if ((actionNum - damageCount) == 5) pMap->drawer.ChipBright();
}

void Player::Destroy()
{
	if (mode != Mode::Destroy) return;

	if (selecter.IsSelectBomb())
	{
		// ”š’e‚ÌƒuƒƒbƒN”j‰ú
		for (size_t i = 0; i < pMap->GetBomb().size(); i++)
		{
			if (pMap->GetBomb()[i].GetPos() == selecter.GetRouteBack())
			{
				pMap->BombDestroy(i, this);
			}
		}
	}

	move = selecter.GetRoutePos(0);
	pMap->bbList.PushBuck(move);
	selecter.EraseRoute(0);
	mode = Mode::Move;


	countStartFlag = 1;
	if (!countStartFlag) return;
	if (++respawnTimer < respawnTimerLimit) return;
	pMap->Respawn();
	pMap->drawer.EraseArrowAndBright(pos);
	pMap->Change(pos, None);
	respawnTimer = 0;
	countStartFlag = 0;
}

void Player::Move()
{
	if (mode != Mode::Move) return;
	if (move.x == -1 && move.y == -1) return;

	pos = move;
	Clamp(pos, pMap->GetMapSize() - Vector2Int(1, 1));
	move = { -1, -1 };

	if (selecter.GetRouteSize() >= 1) mode = Mode::Destroy;
	else 
	{
		mode = Mode::Select;
		actionNum--;
		selecter.Reset();
	}
}

void Player::Draw(const Vector2Int& camera)
{
	selecter.Draw(camera);
	Color color;
	DrawCircle(pMap->GetChipPos(pos).x, pMap->GetChipPos(pos).y, 32, color.Cyan);
	DrawDebugNumber(damageCount, 96);
}