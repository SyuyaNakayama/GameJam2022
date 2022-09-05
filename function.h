#pragma once



// �L�[���𓾂�
void GetKeyState(char* keys, char* oldkeys)
{
	if (keys == nullptr || oldkeys == nullptr)
	{
		return;
	}

	for (int i = 0; i < 256; ++i) oldkeys[i] = keys[i];
	GetHitKeyStateAll(keys);
}

// �A�ԏo�͂ň��ɉ摜������ł��鎞�p�̃��\�[�X�ǂݍ��݊֐�
void LoadDivGraphLine(const TCHAR* fileName, int xNum, int xSize, int ySize, int* handleArray)
{
	if (fileName == nullptr || handleArray == nullptr)
	{
		return;
	}

	LoadDivGraph(fileName, xNum, xNum, 1, xSize, ySize, handleArray);
}

// ������2��̊֐�
int Square(int num)
{
	return num * num;
}

// �f�o�b�O�p�Ɏg���܂�(�A��int�^�̂�)
void DrawDebugNumber(int num, int y = 0)
{
	DrawFormatString(0, y, WHITE, "%d", num);
}

// Anime�^�ϐ��ɑ�����Ďg���ĉ������B
Anime DrawAnimation(Anime anime, int handleArray[], Vector2 center, Vector2 objRadius)
{
	anime = UpdateAnime(anime);
	DrawExtendGraph(center.x - objRadius.x, center.y - objRadius.y,
		center.x + objRadius.x, center.y + objRadius.y,
		handleArray[anime.animeNum], 1);
	return anime;
}

// �L�[���������u��true�ɂȂ�
bool PushButtion(int Buttion, char* keys, char* oldkeys)
{
	if (keys == nullptr || oldkeys == nullptr)
	{
		return false;
	}

	if (!oldkeys[Buttion] && keys[Buttion])
	{
		return true;
	}
	return false;
}