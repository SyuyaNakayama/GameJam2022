#pragma once
// ���W�p�ϐ�
typedef struct Vector2
{
	float x, y;
}Vector2;

// �����A�j���[�V�����`��Ɏg���ϐ�
// ��{�I�ɂ� picNum �� timer �̒l��������������΂����B
typedef struct Anime
{
	int picNum;	// �摜�̖���
	int timer;	// 1���̕`�掞��(�t���[��)
	int nextTimer = timer;	// �^�C�}�[�����l�̋L�^�p
	int animeNum = 0;	// ���݂̉摜�z����L�^���邽�߂̕ϐ�
}Anime;