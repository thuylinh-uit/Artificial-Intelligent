#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
Game thu tu cac nuoc Ger, Ame, Aus, Vie, Ita, Sin, Chin, Rus thi dau vong tron mot luot
Vie da dau voi ger, aus, rus
Ame da dau voi aus, vie
Ita da dau voi sin, rus
Chin da dau voi vie, ita

Trong mot buoi dau mot doi chi dau 1 lan, xep sao cho so buoi it nhat
*/


enum Team
{
	Ger, Ame, Aus, Vie, Ita, Sin, Chin, Rus
};

Team teams[] = { Ger, Ame, Aus, Vie, Ita, Sin, Chin, Rus };

string getTeamName(Team team);

struct Match
{
	Team teams[2];

	void output()
	{
		cout << "Tran giua doi " << getTeamName(teams[0]) << " va doi " << getTeamName(teams[1]) << endl;
	}
	bool operator==(Match &other) const
	{
		if (this->teams[0] == other.teams[0] && this->teams[1] == other.teams[1])
			return true;
		else if (this->teams[0] == other.teams[1] && this->teams[1] == other.teams[0])
			return true;
		else
			return false;
	}
};

void selectionSort(vector<int> matchCount, int *arrayIndices);
bool isIn(vector <Match> Matches, Match match);
bool isIn(Match match, Team team);
Match pickMatch(vector<Match> &remain, vector<Match> day, vector<int> &matchCount, int *teamIndex);
bool isTeamBusy(Team team, vector<Match> day);
vector<Match>::iterator findFirstMatch(Team team, vector<Match>::iterator begin, vector<Match>::iterator end);
bool isMatchViable(Match match, vector<Match> day);


int main()
{
	vector<Match> doneMatches = { { Vie, Ger },{ Vie, Aus },{ Vie, Rus },{ Ame, Aus },{ Ame, Vie },{ Ita, Sin },{ Ita, Rus },{ Chin, Vie },{ Chin, Ita } };

	//Generate matches
	vector <Match> remainingMatches;

	for (int i = 0; i < 8; i++)
	{
		for (int j = i; j < 8; j++)
		{
			if (i == j)
				continue;

			Match match = { Team(i), Team(j) };

			if (isIn(doneMatches, match)) continue;

			else remainingMatches.push_back(match);
		}
	}

	// dem so tran con lai cho moi doi
	vector<int> matchCountForTeams = { 0,0,0,0,0,0,0,0 };
	for (int i = 0; i < remainingMatches.size(); i++)
	{
		matchCountForTeams[remainingMatches.at(i).teams[0]] += 1;
		matchCountForTeams[remainingMatches.at(i).teams[1]] += 1;
	}

	// chon ra doi co so tran nhieu nhat de them vao 1 ngay, neu doi do chua thi dau trong ngay
	int nthDay = 0;
	int teamIndex[] = { 0,1,2,3,4,5,6,7 };
	Match invalid = { Vie, Vie };
	while (!remainingMatches.empty())
	{
		vector<Match> day;
		bool doneDay = false;
		while (!doneDay)
		{
			Match match = pickMatch(remainingMatches, day, matchCountForTeams, teamIndex);
			if (match == invalid)
			{
				nthDay++;
				doneDay = true;
			}
			else
			{
				day.push_back(Match(match));
			}
		}
		cout << "Ngay thu " << nthDay << endl;
		for (auto i = day.begin(); i != day.end(); i++)
		{
			i->output();
		}
	}

	system("pause");
	return 0;
}

string getTeamName(Team team)
{
	switch (team)
	{
	case Ger:
		return "Ger";
		break;
	case Ame:
		return "Ame";
		break;
	case Aus:
		return "Aus";
		break;
	case Vie:
		return "Vie";
		break;
	case Ita:
		return "Ita";
		break;
	case Sin:
		return "Sin";
		break;
	case Chin:
		return "Chin";
		break;
	case Rus:
		return "Rus";
		break;
	default:
		break;
	}
}

Match pickMatch(vector<Match> &remain, vector<Match> day, vector<int> &matchCount, int *teamIndex)
{
	// chon doi co so tran con lai nhieu nhat
	int nthBusiestTeam = 0;
	while (nthBusiestTeam <= 7)
	{
		// sort matchCount, lay doi co index nam o vi tri thu i o lan chay thu i
		selectionSort(matchCount, teamIndex);
		Team team = teams[teamIndex[nthBusiestTeam]];
		auto iterator = remain.begin();
		// tim tran
		while (iterator != remain.end())
		{
			// Tim tran dau tien trong danh sach cac tran con lai co doi 
			//auto match = findFirstMatch(team, iterator, remain.end());
			vector<Match>::iterator match = iterator;
			if (!isIn(*match, team))
			{
				iterator++;
				continue;
			}
			// Kiem tra xem co the xep tran vao ngay duoc khong

			if (isMatchViable(*match, day))
			{
				matchCount[match->teams[0]]--;
				matchCount[match->teams[1]]--;
				Match  m = { match->teams[0], match->teams[1] };
				remain.erase(match);
				return m;
			}
			iterator++;
		}
		// neu khong co tran nao co doi ban thu i thoa, tim cho doi ban thu i+1
		nthBusiestTeam++;
	}
	// neu khong tim duoc doi nao, tra ve tran khong hop le
	return Match({ Vie, Vie });
}

void selectionSort(vector<int> matchCount, int *arrayIndices)
{
	int n = matchCount.size();
	for (int i = 0; i < n; i++)
	{
		int max = i;
		for (int j = i + 1; j < n; j++)
			if (matchCount[arrayIndices[j]] > matchCount[arrayIndices[max]]) max = j;
		swap(arrayIndices[max], arrayIndices[i]);
	}
}

int matchCountForTeam(Team team, vector<Match> remain)
{
	int ans = 0;
	for (auto i = remain.begin(); i != remain.end(); i++)
		if (isIn(*i, team))
			ans += 1;
	return ans;
}

bool isIn(vector <Match> Matches, Match match)
{
	for (vector <Match> ::iterator m = Matches.begin(); m != Matches.end(); m++)
		if (*m == match)
			return true;
	return false;
}

bool isIn(Match match, Team team)
{
	if (match.teams[0] == team || match.teams[1] == team)
		return true;
	return false;

}

vector<Match>::iterator findFirstMatch(Team team, vector<Match>::iterator begin, vector<Match>::iterator end)
{
	auto i = begin;
	for (; i != end; i++)
	{
		if (isIn(*i, team))
			return i;
	}
	return i;
}

bool isTeamBusy(Team team, vector<Match> day)
{
	for (auto i = day.begin(); i != day.end(); i++)
	{
		if (isIn(*i, team))
			return true;
	}
	return false;
}

bool isMatchViable(Match match, vector<Match> day)
{
	if (day.empty())
		return true;
	if (isTeamBusy(match.teams[0], day) || isTeamBusy(match.teams[1], day))
		return false;
	else return true;
}
