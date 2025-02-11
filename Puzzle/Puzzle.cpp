// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>

using namespace std;

#define UP 1
#define DN 2
#define LT 3
#define RT 4
#define NO 0

typedef char TAB[4][4];

struct info
{
	TAB S;
	unsigned g, h, f;
	int d;
	int ID;
	int ID_parents;
};

#define SIZE 500

int id = 0;

typedef struct List
{
	int n;
	info e[SIZE];
	List() { n = 0; }
	void them(info X);
	info timfnho();
	void xuatlist();
	int vitri(TAB X);
};


int nhap();
unsigned count(TAB S);
int sobang(TAB S1, TAB S2);
void ganbang(TAB S1, TAB S2);
void timotrong(TAB S, int &k, int &l);
void bangke(TAB N, int d, TAB S, int k, int l);
int Astart();
void xulyke(info X, int d, TAB S);
void xuat(TAB S);
void timkq();

List O, C, KQ;
TAB S0;
TAB G = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','-' };


int main()
{

	if (nhap() == 0)
	{
		cout << "ERROR";
		return 0;
	}
	if (Astart())
	{
		timkq();
		KQ.xuatlist();
	}
	else
		cout << "No path!";
	return 0;
}



int nhap()
{
	ifstream f("Test.txt");
	if (f.fail())
		cout << "Khong mo duoc file\n";
	int i = 0, j = 0;
	int a, b;
	f >> a >> b;
	if (a != 4 || b != 4)
		return 0;
	while (!f.eof())
	{
		f >> S0[i][j];
		j++;
		if (j == 4)
		{
			j = 0;
			i++;
		}
		if (i == 4)
			break;
	}
	return 1;
}

unsigned count(TAB S)
{
	int d = 0;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (S[i][j] != G[i][j])
				d++;
	return d;
}

int sobang(TAB S1, TAB S2)
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (S1[i][j] != S2[i][j])
				return 0;
	return 1;
}

void ganbang(TAB S1, TAB S2)
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			S1[i][j] = S2[i][j];
}

void timotrong(TAB S, int & k, int & l)
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (S[i][j] == '-')
			{
				k = i;
				l = j;
			}
}

void bangke(TAB N, int d, TAB S, int k, int l)
{
	ganbang(S, N);
	if (d == UP)
	{
		S[k][l] = S[k - 1][l];
		S[k - 1][l] = '-';
	}
	if (d == DN)
	{
		S[k][l] = S[k + 1][l];
		S[k + 1][l] = '-';
	}
	if (d == LT)
	{
		S[k][l] = S[k][l - 1];
		S[k][l - 1] = '-';
	}
	if (d == RT)
	{
		S[k][l] = S[k][l + 1];
		S[k][l + 1] = '-';
	}
}

int Astart()
{
	info X;
	ganbang(X.S, S0);
	X.g = 0;
	X.h = count(S0);
	X.f = X.g + X.h;
	X.d = NO;
	X.ID = id++;
	X.ID_parents = 0;
	O.them(X);
	while (O.n > 0 && O.n <= SIZE)
	{
		X = O.timfnho();
		C.them(X);
		if (sobang(X.S, G) == 1)
			return 1;
		int k, l;
		timotrong(X.S, k, l);
		if (k > 0)
		{
			int d = UP;
			TAB BK;
			bangke(X.S, d, BK, k, l);
			xulyke(X, d, BK);
		}
		if (k < 3)
		{
			int d = DN;
			TAB BK;
			bangke(X.S, d, BK, k, l);
			xulyke(X, d, BK);
		}
		if (l > 0)
		{
			int d = LT;
			TAB BK;
			bangke(X.S, d, BK, k, l);
			xulyke(X, d, BK);
		}
		if (l < 3)
		{
			int d = RT;
			TAB BK;
			bangke(X.S, d, BK, k, l);
			xulyke(X, d, BK);
		}
	}
	return 0;
}

void xulyke(info X, int d, TAB S)
{
	info Y;
	int k;
	if (C.vitri(S) != -1)
		return;
	if (k = O.vitri(S) == -1)
	{
		ganbang(Y.S, S);
		Y.g = X.g + 1;
		Y.h = count(S);
		Y.f = Y.g + Y.h;
		Y.d = d;
		Y.ID = id++;
		Y.ID_parents = X.ID;
		O.them(Y);
	}
	else
		if (X.g + 1 < O.e[k].g)
		{
			O.e[k].g = X.g + 1;
			O.e[k].f = O.e[k].g + O.e[k].h;
			O.e[k].d = d;
			O.e[k].ID_parents = X.ID;
		}
}

void xuat(TAB S)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			cout << S[i][j] << " ";
		cout << "\n";
	}
	cout << "\n";
}

void timkq()
{
	info X = C.e[C.n - 1];
	while (X.ID)
	{
		KQ.them(X);
		for (int i = C.n - 2; i >= 0; i--)
		{
			info T = C.e[i];
			if (T.ID == X.ID_parents)
			{
				X = T;
				break;
			}
		}
	}
	if (!X.ID)
	{
		KQ.them(X);
	}
}


void List::them(info X)
{
	e[n] = X;
	n++;
}

info List::timfnho()
{
	int vt = 0;
	for (int i = 1; i < n; i++)
		if (e[i].f < e[vt].f)
			vt = i;
	info X = e[vt];
	n--;
	for (int i = vt; i < n; i++)
		e[i] = e[i + 1];
	return X;
}

void List::xuatlist()
{
	for (int i = n - 1, k = 0; i >= 0; i--, k++)
	{
		cout << "Buoc " << k << ":\n";
		xuat(e[i].S);
	}
}

int List::vitri(TAB X)
{
	for (int i = 0; i < n; i++)
		if (sobang(X, e[i].S) == 1)
			return i;
	return -1;
}


