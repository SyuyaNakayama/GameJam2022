#pragma once
// ���W�p�ϐ�
typedef struct Screen
{
	int x;
	int y;
}Screen;

// �����A�j���[�V�����`��Ɏg���ϐ�
// ��{�I�ɂ� picNum �� timer �̒l��������������΂����B
typedef struct Anime
{
	int picNum;	// �摜�̖���
	int timer;	// 1���̕`�掞��(�t���[��)
	int nextTimer = timer;	// �^�C�}�[�����l�̋L�^�p
	int animeNum = 0;	// ���݂̉摜�z����L�^���邽�߂̕ϐ�
}Anime;

// �E�B���h�E�̃T�C�Y
const Screen WIN_SIZE = { 800,800 };

// �L�[�{�[�h���p
char keys[256]{}, oldkeys[256]{};

// �F�萔
const int WHITE = GetColor(255, 255, 255);
const int BLACK = GetColor(0, 0, 0);