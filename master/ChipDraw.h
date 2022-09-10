#pragma once
#include "DustEmitter.h"
#include "DebriEmitter.h"
#include "ArrowDraw.h"
#include "BrightDraw.h"
#include "Camera.h"

class ChipDraw
{
private:
	Vector2Int pos;
	Vector2Int number;
	int type;

	// íÖínââèo
	int height;
	Ease ease;
	bool isLanding;
	bool isQuake;

	// îjâÛââèo
	Shake shake;
	bool isBreak;

	bool isDeath;

	int trans;
	int shadow;
	int* brightness;

	int blockG;

	Vector2Int* playerPos;
	Camera* pCamera;
public:
	ChipDraw();
	void Initialze(const Vector2Int& leftTop, const Vector2Int& ary,
		const int type, const bool isDeath, const int blockG);
	void Update();
	void Break();
	void Draw(const Vector2Int& camera);
	void SetBrightness(int* brightness);
	void SetPlayerPos(Vector2Int* playerPos);
	void SetCamera(Camera* pCamera);
	int GetType() { return type; }
	bool GetIsDeath() { return isDeath; }
private:
	void Landing();
	void UpdateShadow();
	void DrawShadow(const Vector2Int& camera);
};
