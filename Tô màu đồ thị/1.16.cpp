/*
	Ý tưởng:
		B1. Biểu diễn các tỉnh Tây Nguyên (5 tỉnh) thành các đỉnh của đồ thị.
			Từ đồ thị chuyển qua ma trận kề(0,1).
		B2. Khởi tạo bậc của các đỉnh Bac[5] bằng 0.
			Màu để tô các đỉnh Mau[5] là màu thứ nhất (màu 1).
		B3. Nhập từ tập tin ma trận kề DoThi[5][5], Bac[5].
		B4. Chọn các đỉnh có bậc lớn nhất để tô trước.
		B5. Với mỗi đỉnh i, duyệt các đỉnh còn lại:
			+) nếu kề đỉnh i và cùng màu với đỉnh i thì tô đỉnh i bằng màu khác
			+) ngược lại giữ nguyên màu
			Số lần duyệt = bậc của đỉnh i.

*/

#include <iostream>
#include <fstream>
using namespace std;

void Input(int DoThi[5][5], int Bac[5]);
int ChonDinh(int Bac[5]);
void ChonMau(int DoThi[5][5], int Mau[5], int Bac[5], int s);
void ToMau(int DoThi[5][5], int Bac[5], int Mau[5]);
int TimMax(int Mau[5]);
void XuatKQ(int Mau[5]);

int main()
{
	int DoThi[5][5], Bac[5] = { 0 }, Mau[5] = { 1,1,1,1,1 };
	Input(DoThi, Bac);
	ToMau(DoThi, Bac, Mau);
	XuatKQ(Mau);
	system("pause");
	return 0;

}

void Input(int DoThi[5][5], int Bac[5])
{
	ifstream file;
	file.open("text16.txt");
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
			file >> DoThi[i][j];
	}
	file.close();
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
			Bac[i] += DoThi[i][j];
	}

	//xuat do thi duoi dang ma tran ke:
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
			cout << DoThi[i][j] << " ";
		cout << endl;
	}
	cout << "\n\n";
}

int ChonDinh(int Bac[5])
{
	int dinh = 0;
	for (int i = 1; i < 5; i++)
	{
		if (Bac[i] > Bac[dinh])
			dinh = i;
	}
	return dinh;
}

void ChonMau(int DoThi[5][5], int Mau[5], int Bac[5], int s)
{
	for (int lan = 0; lan < Bac[s]; lan++)
	{
		for (int i = 0; i < 5; i++)
		{
			if (DoThi[s][i] != 0 && Mau[s] == Mau[i])
				Mau[s]++;
		}
	}
}

void ToMau(int DoThi[5][5], int Bac[5], int Mau[5])
{
	for (int i = 0; i < 5; i++)
	{
		int s = ChonDinh(Bac);
		ChonMau(DoThi, Mau, Bac, s);
		Bac[s] = 0;
	}
}

int TimMax(int Mau[5])
{
	int MAX = Mau[0];
	for (int i = 1; i < 5; i++)
		if (MAX < Mau[i])
			MAX = Mau[i];
	return MAX;
}

void XuatKQ(int Mau[5])
{
	for (int i = 0; i < 5; i++)
	{
		cout << "Dinh " << i + 1 << "- Mau " << Mau[i] << endl;
	}
	cout << "\nTong so mau can thiet: " << TimMax(Mau) << "\n\n";
}
