// 1.17.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
using namespace std;
int ChonDinh(int Bac[], int n)
{
	int temp = 0;
	for (int i = 1; i < n; i++)
		if (Bac[i] > Bac[temp] && Bac[i] >= 0)
			temp = i;
	return temp;
}
int TimBac(int MT[][100], int n, int i)
{
	int Bac = 0;
	for (int j = 0; j < n; j++)
		if (MT[i][j])
			Bac++;
	return Bac;
}
int ToMau(int Mau[], int MT[][100], int n, int k, int &m)
{
	for (int color = 1; color <= m; color++)
	{
		bool OK = true;
		for (int j = 0; j < n; j++)
			if (MT[k][j] && color == Mau[j])
				OK = false;
		if (OK)
			return color;
	}
	return ++m;
}
int main()
{
	int n, m = 1;
	int MT[100][100], Bac[100], Mau[100] = { 0 };
	ifstream test("Test.txt");
	if (test.is_open())
	{
		test >> n;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				test >> MT[i][j];
		test.close();
	}
	else cout << "Khong mo duoc file test";
	for (int i = 0; i < n; i++)
		Bac[i] = TimBac(MT, n, i);
	cout << "Dua vao ban do, ta duoc ma tran ke:\n";
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cout << MT[i][j] << " ";
		cout << endl;
	}
	cout << endl;
	for (int i = 0; i < n; i++)
	{
		int k = ChonDinh(Bac, n);
		Mau[k] = ToMau(Mau, MT, n, k, m);
		cout << "Tinh thu " << k << ": mau " << Mau[k] << endl;
		Bac[k] = -1;
	}
	cout << "\nSo mau dung de to ban do la: " << m << endl;
}



