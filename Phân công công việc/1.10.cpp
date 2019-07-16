
#include <iostream>
#include <utility>
using namespace std;

void SapXep(int T[], int ID[], int n)
{
	for (int i = 1; i <= n; i++)
		for (int j = i + 1; j <= n; j++)
			if (T[i] < T[j])
			{
				swap(T[i], T[j]);
				swap(ID[i], ID[j]);
			}
}
int ChonMay(int M[], int m)
{
	int vt = 1;
	for (int i = 2; i <= m; i++)
		if (M[i] < M[vt])
			vt = i;
	return vt;
}
int ThoiGianMay(int j, int n, int ID[], int T[])
{
	for (int i = 1; i <= n; i++)
		if (ID[i] == j)
			return T[i];
}

int x = 2;
int main()
{
	x = x + 1;
	cout << "là x: " << x;
	int T[100], ID[100], M[100] = { 0 }, KQ[100];
	int n, m;
	cout << "Nhap so luong may: ";
	cin >> m;
	cout << "Nhap so luong cong viec: ";
	cin >> n;
	cout << "Nhap thoi gian thuc hien cong viec tuong ung: ";
	for (int i = 1; i <= n; i++)
	{
		cin >> T[i];
		ID[i] = i;
	}
	SapXep(T, ID, n);
	for (int i = 1; i <= n; i++)
	{
		int temp = ChonMay(M, m);
		KQ[ID[i]] = temp;
		M[temp] += T[i];
	}
	for (int i = 1; i <= m; i++)
	{
		cout << "\tMay " << i << ": \n";
		for (int j = 1; j <= n; j++)
			if (KQ[j] == i)
				cout << "Cong viec " << j << " - " << ThoiGianMay(j, n, ID, T) << " tieng" << endl;
	}
	cout << "\nThoi gian hoan thanh tat ca cong viec: ";
	int MAX = M[1];
	for (int i = 2; i <= m; i++)
		if (MAX < M[i])
			MAX = M[i];
	cout << MAX << " tieng" << endl;
	return 0;
}





