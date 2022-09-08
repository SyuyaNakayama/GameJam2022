#pragma once
#include "Ease.h"
#include "DustEmitter.h"
#include "Camera.h"

class ChipDraw
{
private:
	Vector2Int pos;
	int height;
	Ease ease;
	DustEmitter dustE;
	bool isLanding;
	bool isEmit;
	int trans;
	int graph;
	Camera* pCamera;
public:
	ChipDraw();
	void Initialze(const Vector2Int& leftTop, const Vector2Int& ary, const int graph);
	void Update();
	void Draw(const Vector2Int& camera);
	void SetCamera(Camera* pCamera);
private:
	void Landing();
};

