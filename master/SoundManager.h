#pragma once
#include <vector>

using namespace std;

enum Sound { BGM, SE };

class SoundManager
{
private:
	vector<int> bgmHandle;
	vector<int> seHandle;
public:
	void Load();
	void PlayBGM(int index, bool loopFlag = true);
	void PlaySE(int index);
	void StopBGM(int index);
	void SetVolume(Sound sound, int index, int volume); // volume‚Í0~255
public:
	static SoundManager* GetInstance();
private:
	SoundManager() = default;
	~SoundManager() = default;
	SoundManager(const SoundManager&) = delete;
	const SoundManager& operator=(const SoundManager&) = delete;
};