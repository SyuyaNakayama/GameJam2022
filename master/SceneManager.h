#pragma once
#include "Ease.h"
#include "Vector2.h"

class SceneManager
{
private:
	int scene = 0;
	int next = 0;
	int trans = 0;
	Ease2 ease;
	bool isEase = false;
	Vector2Int winSize;
	bool isProcessing = false;
	bool isChanged = false;
public:
	void Initialze(const int scene, const Vector2Int& winSize);
	void Change(const int nextScene);
	void Update();
	void DrawCurtain();
private:
	void Late();
	void Dawn();
public:
	void SetScene(const int scene) { this->scene = scene; }
	int GetScene() { return scene; }
	bool IsProcessing() { return isProcessing; }
	bool IsChanged() { return isChanged; }
};

