#include "SceneManager.h"
#include "DxLib.h"

void SceneManager::Initialze(const int scene, const Vector2Int& winSize)
{
	this->scene = scene;
	next = scene;
	trans = 0;
	ease.Initialize(0.1f, 0.1f);
	isEase = false;
	this->winSize = winSize;
	isProcessing = false;
	isChanged = false;
}

void SceneManager::Change(const int nextScene)
{
	if (isProcessing) return;
	next = nextScene;
	trans = 0;
	ease.Initialize(0.1f, 0.1f);
	isEase = true;
	isProcessing = true;
	isChanged = false;
}

void SceneManager::Update()
{
	isChanged = false;
	if (!isProcessing) return;

	ease.Update(isEase);
	trans = (int) ease.In(0.0f, 255.0f, 2.0f);

	Late();
	Dawn();
}


void SceneManager::Late()
{
	if (isEase && trans >= 255)
	{
		isEase = false;
		isChanged = true;
		scene = next;
	}
}

void SceneManager::Dawn()
{
	if (!isEase && trans <= 0)
	{
		isProcessing = false;
	}
}

void SceneManager::DrawCurtain()
{
	if (!isProcessing) return;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, trans);
	DrawBox(0, 0, winSize.x, winSize.y, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
