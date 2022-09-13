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
	string str;
public:
	void Load();
	void Update(int newScore);
	void Draw(Font& font);
	void Reset();
};