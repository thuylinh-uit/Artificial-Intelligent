#include <iostream>
#include <fstream>
#include <conio.h>
using namespace std;

struct Dinh {
	int name;
	int g;//độ dài đường đi từ đỉnh S đến chính nó
	int f;
	int pre;//đỉnh trước nó
};

int DT[50][50];
int n;
int h[50];

Dinh Open[50];
int nO = 0;
Dinh Close[50];
int nC = 0;

void DocFile();
void ThemDinh(Dinh N, Dinh Set[], int &nS);	//Thêm đỉnh vào tập hợp Set
void XoaDinh(int vt, Dinh Set[], int &nS);	//Xóa đỉnh trong tập Set tại ví trí vt
int NhoNhat();								//trả về vị trí trong Open có g nhỏ nhất
int Member(int node, Dinh Set[], int nS);//kiểm tra đỉnh tên là node có là phần tử của tập Set
										 //nếu có thì return về vị trí trong tập Set, 
										 //không thì return -1
void Astar(int S, int G);
void Path(int S, int G);

int main() {

	DocFile();

	int S, G, TG;//S: đỉnh bắt đầu, G: đỉnh kết thúc, TG: đỉnh trung gian
	cout << "Nhap dinh bat dau: "; cin >> S;
	cout << "Nhap dinh ket thuc: "; cin >> G;

	cout << "\n\t*****\n";

	Astar(S, G);
	Path(S, G);

	_getch();
	return 0;
}

void DocFile() {
	ifstream file;
	file.open("Dothi.txt");
	file >> n;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			file >> DT[i][j];
	for (int i = 0; i < n; i++)
		file >> h[i];
	file.close();
}

void ThemDinh(Dinh N, Dinh Set[], int &nS) {
	Set[nS] = N;
	nS++;
}

void XoaDinh(int vt, Dinh Set[], int &nS) {
	for (int i = vt; i < nS - 1; i++)
		Open[i] = Open[i + 1];
	nS--;
}

int NhoNhat() {
	int min = Open[0].g;
	int vt = 0;
	for (int i = 0; i<nO; i++)
		if (min > Open[i].g) {
			min = Open[i].g;
			vt = i;
		}
	return vt;
}

int Member(int node, Dinh Set[], int nS) {
	for (int i = 0; i < nS; i++)
		if (Set[i].name == node)
			return i;
	return -1;
}

void Astar(int S, int G)
{
	Dinh N;
	N.name = S;
	N.g = 0;
	N.f = h[S];
	N.pre = 0;
	ThemDinh(N, Open, nO);

	while (nO != 0)
	{
		int vt = NhoNhat();
		Dinh N = Open[vt];
		ThemDinh(N, Close, nC);
		if (N.name == G)
			break;
		else {
			for (int node = 0; node < n; node++)
			{
				int belong = Member(node, Close, nC);
				if (belong == -1 && DT[N.name][node] > 0)
				{
					int k = Member(node, Open, nO);
					if (k >= 0)
					{
						Dinh Q;
						Q = Open[k];
						if (N.g + DT[N.name][Q.name] < Q.g)
						{
							Open[k].g = N.g + DT[N.name][Q.name];
							Open[k].f = Open[k].g + h[Q.name];
							Open[k].pre = N.name;
						}
					}
					else
					{
						Dinh Q;
						Q.name = node;
						Q.g = N.g + DT[N.name][Q.name];
						Q.f = Q.g + h[Q.name];
						Q.pre = N.name;
						ThemDinh(Q, Open, nO);
					}
				}
			}
		}
		XoaDinh(vt, Open, nO);
	}
}

void Path(int S, int G)
{
	int vtG = Member(G, Close, nC);
	if (vtG >= 0) {
		cout << "\nDo dai duong di tu " << S << " den " << G << " la: " << Close[vtG].g << endl;
		cout << "Duong di la: " << G;
		int k = vtG;
		while (Close[k].pre != S) {
			cout << " <-- " << Close[k].pre;
			k = Member(Close[k].pre, Close, nC);
		}
		cout << " <-- " << S << endl;
	}
	else//vtG = -1
		cout << "Khong co duong di tu " << S << " den " << G << endl;
}