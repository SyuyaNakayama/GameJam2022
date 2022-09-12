#pragma once
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include "Font.h"

using namespace std;

class RankingManager
{
private:
	string fileName = "Resources/Ranking/Ranking.txt";
	vector<int>scoreList;
	vector<string>rankStr = { "1ˆÊ ","2ˆÊ ","3ˆÊ ","4ˆÊ ","5ˆÊ " };
	string str;
public:
	RankingManager();
	void Update(int newScore);
	void Draw(Font& font);
};