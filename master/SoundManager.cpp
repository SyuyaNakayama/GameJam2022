#include "SoundManager.h"
#include "DxLib.h"
#include "function.h"

void SoundManager::Load()
{
	// BGMì«Ç›çûÇ›
	bgmHandle =
	{ 
		LoadSoundMem("Resources/Sound/BGM/Title.mp3"),
		LoadSoundMem("Resources/Sound/BGM/Prologue.mp3"),
		LoadSoundMem("Resources/Sound/BGM/Tutrial.mp3"),
		LoadSoundMem("Resources/Sound/BGM/Play.mp3"), 
		LoadSoundMem("Resources/Sound/BGM/Result.mp3"),
	};

	// SEì«Ç›çûÇ›
	seHandle =
	{
		LoadSoundMem("Resources/Sound/SE/break.mp3"),
		LoadSoundMem("Resources/Sound/SE/bomb.mp3"),
		LoadSoundMem("Resources/Sound/SE/coin.mp3"),
		LoadSoundMem("Resources/Sound/SE/crystal.mp3"),
		LoadSoundMem("Resources/Sound/SE/fall.mp3")
	};
}

void SoundManager::PlayBGM(int index, bool loopFlag)
{
	if (CheckSoundMem(bgmHandle[index])) { return; }
	if (!loopFlag) { PlaySoundMem(bgmHandle[index], DX_PLAYTYPE_BACK); }
	else { PlaySoundMem(bgmHandle[index], DX_PLAYTYPE_LOOP); }
}

void SoundManager::PlaySE(int index)
{
	if (CheckSoundMem(bgmHandle[index])) { return; }
	PlaySoundMem(seHandle[index], DX_PLAYTYPE_BACK);
}

void SoundManager::StopBGM(int index)
{
	StopSoundMem(bgmHandle[index]);
}

void SoundManager::SetVolume(Sound sound, int index, int volume)
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

SoundManager* SoundManager::GetInstance()
{
	static SoundManager instance;
	return &instance;
}
