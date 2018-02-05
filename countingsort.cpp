#include <bits/stdc++.h>
using namespace std;

void countingsort(vector<int> &arr)
{
	auto k = arr.begin();
	int m(*k), M(*k);
	for (++k; k != arr.end(); ++k)
	{
		m = min(m, *k);
		M = max(M, *k);
	}
	vector<int> count; count.resize(M-m);
	for (auto x : arr)
		++count[x-m];

	for (int i = 1; i < M-m; ++i)
		count[i]+=count[i-1];
	vector<int> ret; ret.resize(arr.size());
	for (auto x : arr)
		ret[(count[x-m]--)-1] = x;
	arr = ret;
}

//usage
int main()
{
	vector<int> arr;
	int size = 20;
	for (int i = 0; i < size; ++i)
		arr.push_back(rand()%size-size/2);
	cout << "Before: ";
	for (auto x : arr)
		cout << x << ' ';
	cout << '\n';
	cout << "After: ";
	countingsort(arr);
	for (auto x : arr)
		cout << x << ' ';
	cout << '\n';
}
