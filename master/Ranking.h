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
	vector<string>rankStr = { "1�� ","2�� ","3�� ","4�� ","5�� " };
	string str;
public:
	RankingManager();
	void Update(int newScore);
	void Draw(Font& font);
};