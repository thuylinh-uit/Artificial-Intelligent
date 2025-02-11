// Prim.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
using namespace std;

struct Edge
{
	int First;
	int Second;
	int Distance;
};

map<int,Edge> Open;
set<int> Set;
vector<Edge> Path;
vector<string> Dinh;
vector<Edge> Canh;
int n, m;

bool Check(int Or1, int Or2);
int Input();
void Prim();
bool Sort(Edge i, Edge j);


int main()
{
	if (!Input())
	{
		cout << "Error!";
		return 0;
	}
	Prim();
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

void Prim()
{
	int A = 0;
	Set.insert(A);
	while (Set.size() < n)
	{
		for (int i = 0; i < Canh.size(); i++)
			if (Canh[i].First == A || Canh[i].Second == A)
				Open[Canh[i].Distance] = Canh[i];
		for (auto i = Open.begin(); i != Open.end(); i++)
		{
			Edge M = i->second;
			if (Set.find(M.First) == Set.end() || Set.find(M.Second) == Set.end())
			{
				Path.push_back(M);
				if (Set.find(M.First) == Set.end())
					A = M.First;
				else
					A = M.Second;
				Set.insert(A);
				break;
			}
		}
	}
}


