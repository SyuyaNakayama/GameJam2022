#pragma once
#include "Vector2.h"
// ������2��̊֐�
int Square(int num);
// �������[�v������֐�
void NumberLoop(int& num, int max, int min = 0);
// �ő�l�ŏ��l��ݒ�
void Clamp(int& num, int max, int min = 0);
// �f�o�b�O�p�Ɏg���܂�(�A��int�^�̂�)
void DrawDebugNumber(int num, int y = 0);
void DrawBoxWithVectorInt(Vector2Int pos, Vector2Int rad, int color, bool fillFlag = 1);