#pragma once
#include <vector>

using namespace std;

enum Sound { BGM, SE };

class SoundManeger
{
private:
	vector<int> bgmHandle;
	vector<int> seHandle;
public:
	SoundManeger();
	void PlayBGM(int index, bool loopFlag = true);
	void PlaySE(int index);
	void StopBGM(int index);
	void SetVolume(Sound sound, int index, int volume); // volume‚Í0~255
};