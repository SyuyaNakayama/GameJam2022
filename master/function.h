#pragma once
#include "Vector2.h"
// �ő�l�ŏ��l��ݒ�
void Clamp(int& num, int max, int min = 0);
void Clamp(float& num, float max, float min = 0);
void Clamp(Vector2Int& num, Vector2Int max, Vector2Int min = { 0,0 });

bool IsInsideValue(int num, int max, int min = 0);
// �f�o�b�O�p�Ɏg���܂�(�A��int�^�̂�)
void DrawDebugNumber(int num, int y = 0);
void DrawDebugNumber(float num, int y = 0);
void DrawBoxWithVectorInt(Vector2Int pos, Vector2Int rad, int color, bool fillFlag = 1);