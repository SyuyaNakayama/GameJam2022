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
	vector<string>rankStr = { "1位 ","2位 ","3位 ","4位 ","5位 " };
	string str;
public:
	RankingManager();
	void Update(int newScore);
	void Draw(Font& font);
};