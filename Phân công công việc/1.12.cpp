/**
*	Ý tưởng:
*		B1:phân tập chi tiết máy ra làm 2 mảng:
*			Mảng tmp01: gồm các chi tiết máy gia công trên máy 1 nhanh hơn gia công trên máy 2
*		 	Mảng tmp02: gồm các chi tiết máy gia công trên máy 2 nhanh hơn gia công trên máy 1
*	   	B2: sort tmp01 tăng dần theo thời gian gia công trên máy 1
*	   		sort tmp02 giảm dần theo thời gian gia công trên máy 2
*	   	B3: gộp danh sách 2 mảng theo thứ tự tmp01 đến tmp02 vào mảng s
*	   	=> Mảng s chính là thứ tự cần gia công để được thời gian nhanh nhất
*  IDE: code::block 17.12 / G++ 14
*
Instance:
11
3 6 4 3 4 2 7 5 5 6 12
4 5 5 2 3 3 6 6 4 7 2
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define piii pair<int, pair<int, int>> 		// pair<id, pair<a, b>>
int main() {
	int n;
	cin >> n;	// instance: n = 11
	vector<piii> s(n), tmp01, tmp02;
	for (int i = 0; i < n; ++i) {
		cin >> s[i].second.first;
		s[i].first = i;
	}
	// --------------------- B1 --------------------
	for (int i = 0; i < n; ++i) {
		cin >> s[i].second.second;
		if (s[i].second.first <= s[i].second.second) {
			tmp01.push_back(s[i]);
		}
		else {
			tmp02.push_back(s[i]);
		}
	}
	// --------------------- B2 --------------------
	sort(tmp01.begin(), tmp01.end(), [&](piii i, piii j) {
		return i.second.first < j.second.first;
	});
	sort(tmp02.begin(), tmp02.end(), [&](piii i, piii j) {
		return i.second.second > j.second.second;
	});
	// --------------------- B3 --------------------
	s.clear();
	for (auto i : tmp01) {
		s.push_back(i);
	}
	for (auto i : tmp02) {
		s.push_back(i);
	}
	// --------------------- final -----------------
	int time_M1 = 0, time_M2 = 0;
	for (int i = 0; i < n; ++i) {
		time_M1 += s[i].second.first;
		time_M2 = max(time_M1, time_M2) + s[i].second.second;
	}
	cout << "THOI GIAN HOAN THANH: " << time_M2 << '\n';
	cout << "THU TU GIA CONG CHI TIET: ";
	for (int i = 0; i < n; ++i) {
		cout << s[i].first << ' ';
	}
	return 0;
}