
/*	Y tuong:
	1. Xep lai thu tu cong viec theo tong thoi gian thuc hien cua m nguoi tu cao den thap
	2. Chon nguoi thuc hien cong viec i sao cho:
		min(tong thoi gian nguoi do da lam + thoigian nguoi do thuc hien cong viec i)
	*Thuat toan ap dung nguyn li thu tu o (1.) va nguyen li tham lam o (2.)
*/

#include <fstream>
#include <iostream>
using namespace std;

void Input(int A[3][8], int ID[8]);
void Tong(int A[3][8], int a[8]);
void SapXep(int A[3][8], int a[8], int ID[8]);
int ChonNguoi(int A[3][8], int i, int N[3]);
void PhanCong(int A[3][8], int N[3], int KQ[8], int ID[8], int TG[8]);
int TimMax(int N[3]);
void Output(int KQ[8], int TG[8], int N[3]);

int main()
{
	int A[3][8], a[8], ID[8], N[3] = { 0 }, KQ[8], TG[8];
	Input(A, ID);
	Tong(A, a);
	SapXep(A, a, ID);
	PhanCong(A, N, KQ, ID, TG);
	Output(KQ, TG, N);
	system("pause");
	return 0;
}

void Input(int A[3][8], int ID[8])
{
	ifstream file;
	file.open("text11.txt");
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j<8; j++)
			file >> A[i][j];
	}
	file.close();

	for (int i = 0; i < 8; i++)
		ID[i] = i;

	//xuat:
	cout << "\nPhan 8 cong viec cho 3 nguoi.\nThoi gian tij de nguoi thu i thuc hien cong viec thu j duoc cho trong bang sau:\n\n";
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 8; j++)
		{
			cout << A[i][j] << " ";
		}
		cout << endl;
	}
	cout << "\n\n";

}

void Tong(int A[3][8], int a[8])
{
	for (int i = 0; i < 8; i++)
		a[i] = A[0][i] + A[1][i] + A[2][i];
}

void SapXep(int A[3][8], int a[8], int ID[8])
{
	for (int i = 0; i < 7; i++)
	{
		for (int j = i + 1; j < 8; j++)
		{
			if (a[i] < a[j])
			{
				swap(a[i], a[j]);
				swap(A[0][i], A[0][j]);
				swap(A[1][i], A[1][j]);
				swap(A[2][i], A[2][j]);
				swap(ID[i], ID[j]);
			}
		}
	}
}

int ChonNguoi(int A[3][8], int i, int N[3])
{
	int temp[3];
	for (int t = 0; t < 3; t++)
	{
		temp[t] = A[t][i] + N[t];
	}
	int vt = 0;
	for (int t = 1; t < 3; t++)
	{
		if (temp[t] < temp[vt])
			vt = t;
	}
	return vt;
}

void PhanCong(int A[3][8], int N[3], int KQ[8], int ID[8], int TG[8])
{
	for (int i = 0; i < 8; i++)
	{
		int c = ChonNguoi(A, i, N);
		KQ[ID[i]] = c;
		TG[ID[i]] = A[c][i];
		N[c] += A[c][i];
	}
}

int TimMax(int N[3])
{
	int MAX = N[0];
	for (int i = 1; i < 3; i++)
		if (MAX < N[i])
			MAX = N[i];
	return MAX;
}

void Output(int KQ[8], int TG[8], int N[3])
{
	cout << "--------------------------------------------------------------------------\n";
	cout << "Cong viec-i\t\t\tNguoi-j\t\t\t\tThoi gian-tij\n";
	cout << "-----------\t\t\t-------\t\t\t\t-------------\n";
	for (int i = 0; i < 8; i++)
	{
		cout << "  \t" << i + 1 << "       \t\t\t" << KQ[i] + 1 << "       \t\t\t" << TG[i] << "\n\n";
	}
	cout << "Tong thoi gian thuc hien tat ca cac cong viec: " << TimMax(N) << "\n";
	cout << "--------------------------------------------------------------------------\n";
}