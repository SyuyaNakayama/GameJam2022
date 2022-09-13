#include "Ranking.h"
#include <cassert>
#include "function.h"
#include "enum.h"

void RankingManager::Load()
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
	for (size_t i = 1; i <= 5; i++) { rankStr.push_back(to_string(i) + "�� "); }

	scoreList.push_back(newScore);
	sort(scoreList.begin(), scoreList.end());
	reverse(scoreList.begin(), scoreList.end());
	scoreList.pop_back();
	str.clear();
	for (size_t i = 0; i < scoreList.size(); i++)
	{
		str += rankStr[i] + to_string(scoreList[i]) + "�_\n";
	}
	ofstream rankingOut("Resources/Ranking/Ranking.txt");
	rankingOut << str << flush;
}

void RankingManager::Draw(Vector2Int pos,Font& font)
{
	Color color;
	font.DrawUseFont({ 750,300 }, color.White, str.c_str(), FontSize::LL);
}

void RankingManager::Reset()
{
	ofstream rankingCreate("Resources/Ranking/Ranking.txt");
	string rStr = "1�� 0�_\n2�� 0�_\n3�� 0�_\n4�� 0�_\n5�� 0�_\n";
	rankingCreate << rStr << flush;
}