// Kruskal.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// TH05.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

struct Edge
{
	int First;
	int Second;
	int Distance;
};

set<int> Open;
vector<Edge> Path;
vector<string> Dinh;
vector<Edge> Canh;
vector<int> Par;
int n, m;

bool Check(int Or1, int Or2);
int Input();
void Kruskal();
bool Sort(Edge i, Edge j);


int main()
{
	if (!Input())
	{
		cout << "Error!";
		return 0;
	}
	Kruskal();
	int totalpath = 0;
	cout << "Path:";
	for (auto i : Path)
	{
		cout << "\t" << Dinh[i.First] << "-" << Dinh[i.Second] << endl;
		totalpath += i.Distance;
	}
	cout << "Total distance: " << totalpath << endl;
	return 0;
}

int Input()
{
	ifstream f("Test.txt");
	if (f.fail())
		return 0;
	f >> n >> m;
	for (int i = 0; i < n; i++)
	{
		string A;
		f >> A;
		Dinh.push_back(A);
	}
	for (int i = 0; i < m; i++)
	{
		Edge A;
		f >> A.First >> A.Second >> A.Distance;
		Canh.push_back(A);
	}
	f.close();
	return 1;
}

void Kruskal()
{
	sort(Canh.begin(), Canh.end(), Sort);
	for (int i = 0; i < n; i++)
		Par.push_back(i);
	while (Path.size() < n - 1)
	{
		Edge a = Canh.back();
		Canh.pop_back();
		if (Check(a.First, a.Second))
		{
			Open.insert(a.First);
			Open.insert(a.Second);
			Par[a.First] = Par[a.Second] = min(Par[a.First], Par[a.Second]);
			Path.push_back(a);
			for (int i = 0; i < Path.size(); i++)
			{
				Par[Path[i].First] = Par[Path[i].Second] = min(Par[Path[i].First], Par[Path[i].Second]);
			}
		}
	}
}

bool Check(int V1, int V2)
{
	if (Par[V1] == Par[V2])
		return false;
	return true;
}

bool Sort(Edge i, Edge j)
{
	return (i.Distance > j.Distance);
}


