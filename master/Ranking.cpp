#include "Ranking.h"
#include <cassert>
#include "function.h"
#include "enum.h"

RankingManager::RankingManager()
{
	ifstream ranking(fileName);
	assert(!ranking.fail());
	string buf;

	while (getline(ranking, buf))
	{
		string tempStr(buf);
		tempStr.erase(tempStr.begin(), tempStr.begin() + 4);
		scoreList.push_back(stoi(tempStr));
	}
}

void RankingManager::Update(int newScore)
{
	vector<string>rankStr;
	for (size_t i = 1; i <= 5; i++) { rankStr.push_back(to_string(i) + "ˆÊ "); }

	scoreList.push_back(newScore);
	sort(scoreList.begin(), scoreList.end());
	reverse(scoreList.begin(), scoreList.end());
	scoreList.pop_back();
	for (size_t i = 0; i < scoreList.size(); i++)
	{
		str += rankStr[i] + to_string(scoreList[i]) + "“_\n";
	}
	ofstream rankingOut("Resources/Ranking/Ranking.txt");
	rankingOut << str << flush;
}

void RankingManager::Draw(Font& font)
{
	Color color;
	font.DrawUseFont({ 400,250 }, color.White, str.c_str(), FontSize::LL);
}