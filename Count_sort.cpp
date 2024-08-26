#include<cstdio>
#include<iostream>
#include<omp.h>
#include<vector>

using namespace std;

void Count_sort(vector<int> &a) {
	vector<int>temp(a.size(), 0);
	int count = 0;
#pragma omp parallel for private(count)
	for (int i = 0; i < a.size(); i++) {
		count = 0;
		for (int j = 0; j < a.size(); j++) {
			if (a[j] < a[i])	count++;
			else if (a[j] == a[i] && j < i)	count++;
		}
		temp[count] = a[i];
	}
#pragma omp parallel for 
	for (int i = 0; i < a.size(); i++) {
		a[i] = temp[i];
	}
	return;
}

int main() {
	omp_set_num_threads(8);
	int n = 10;
	vector<int>a(n, 0);
	for (int i = 0; i < n; i++)	a[i] = n - i;
	Count_sort(a);
	for (auto& it : a)cout << it << endl;
	return 0;
}
