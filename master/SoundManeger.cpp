#include "SoundManeger.h"
#include "DxLib.h"
#include "function.h"

SoundManeger::SoundManeger()
{
	// BGMì«Ç›çûÇ›
	bgmHandle = {};

	// SEì«Ç›çûÇ›
	seHandle = {};
}

void SoundManeger::PlayBGM(int index, bool loopFlag)
{
	if (CheckSoundMem(bgmHandle[index])) { return; }
	if (!loopFlag) { PlaySoundMem(bgmHandle[index], DX_PLAYTYPE_BACK); }
	else { PlaySoundMem(bgmHandle[index], DX_PLAYTYPE_LOOP); }
}

void SoundManeger::PlaySE(int index)
{
	if (CheckSoundMem(bgmHandle[index])) { return; }
	PlaySoundMem(seHandle[index], DX_PLAYTYPE_BACK);
}

void SoundManeger::StopBGM(int index)
{
	StopSoundMem(bgmHandle[index]);
}

void SoundManeger::SetVolume(Sound sound, int index, int volume)
{
	Clamp(volume, 255);
	switch (sound)
	{
	case BGM:
		ChangeVolumeSoundMem(volume, bgmHandle[index]);	break;
	case SE:
		ChangeVolumeSoundMem(volume, seHandle[index]);	break;
	}
}