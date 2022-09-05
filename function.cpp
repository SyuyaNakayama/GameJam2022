#include "DxLib.h"
#include "numbering.h"
#include "function.h"

void GetKeyState()
{
	for (int i = 0; i < 256; ++i) oldkeys[i] = keys[i];
	GetHitKeyStateAll(keys);
}

// �A�ԏo�͂ň��ɉ摜������ł��鎞�p�̃��\�[�X�ǂݍ��݊֐�
void LoadDivGraphLine(const TCHAR* fileName, int xNum, int xSize, int ySize, int* handleArray)
{
	LoadDivGraph(fileName, xNum, xNum, 1, xSize, ySize, handleArray);
}

// �������[�v������֐�
int NumberLoop(int num, int max, int min)
{
	if (num >= max)num = min;
	if (num < min)num = max - 1;
	return num;
}

// ������2��̊֐�
int Square(int num)
{
	return num * num;
}

// �f�o�b�O�p�Ɏg���܂�(�A��int�^�̂�)
void DrawDebugNumber(int num, int y)
{
	DrawFormatString(0, y, WHITE, "%d", num);
}

// �g�����Ƃ͂Ȃ��֐��ł�
Anime UpdateAnime(Anime anime)
{
	anime.timer--;
	anime.timer = NumberLoop(anime.timer, anime.nextTimer);

	if (anime.timer == 0)anime.animeNum++;

	anime.animeNum = NumberLoop(anime.animeNum, anime.picNum);

	return anime;
}

// Anime�^�ϐ��ɑ�����Ďg���ĉ������B
Anime DrawAnimation(Anime anime, int handleArray[], int x1, int y1, int x2, int y2)
{
	anime = UpdateAnime(anime);
	DrawExtendGraph(x1, y1, x2, y2, handleArray[anime.animeNum], 1);
	return anime;
}
Anime DrawAnimation(Anime anime, int handleArray[], Screen center, Screen objRadius)
{
	anime = UpdateAnime(anime);
	DrawExtendGraph(center.x, center.y, objRadius.x, objRadius.y, handleArray[anime.animeNum], 1);
	return anime;
}

bool PushButtion(int Buttion)
{
	if (!oldkeys[Buttion] && keys[Buttion])
	{
		return true;
	}
	return false;
}