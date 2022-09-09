#pragma once
#include "Ease.h"
#include "DustEmitter.h"
#include "DebriEmitter.h"
#include "Camera.h"

class ChipDraw
{
public:
	enum BlockType
	{
		None,
		Plain,
		Gold,
		Ore,
		Bomb,
	};
private:
	Vector2Int pos;
	int height;
	Ease ease;
	int type;
	
	DustEmitter dustE;
	bool isLanding;
	bool isEmit;
	
	DebriEmitter debriE;
	Shake shake;
	bool isBreak;
	bool isEmit2;
	
	int trans;
	int blockG;
	int debriG;

	Camera* pCamera;
public:
	ChipDraw();
	void Initialze(const Vector2Int& leftTop, const Vector2Int& ary, const int type, const int blockG, const int debriG);
	void Update();
	void Break();
	void Draw(const Vector2Int& camera);
	void SetCamera(Camera* pCamera);
private:
	void Landing();
	void EmitDebris();
};

