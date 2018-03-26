#include <bits/stdc++.h>
using namespace std;

#define arrtype int //replace with a struct (that has a comparator) to use key/values
/*
struct arrtype
{
	int key;	
	int val;
	bool operator<=(arrtype other) //only this operator is required
	{
		return key <= other.key;
	}
};
*/

void merge(vector<arrtype> &arr, int l, int m, int r) //m is last character of first partition
{
	vector<arrtype> ret(r-l+1);
	int a = l, b = m+1;
	int i = 0;
	while (a <= m || b <= r)
	{
		if ((a <= m && arr[a] <= arr[b]) || b > r)
			ret[i++] = arr[a++];
		else
			ret[i++] = arr[b++];
	}
	for (int j = 0; j < i; ++j)
		arr[l+j] = ret[j];
}
void mergesort(vector<arrtype> &arr, int l, int r)
{
	if (l == r)
		return;
	int m = (l+r)/2;
	mergesort(arr,l,m);
	mergesort(arr,m+1,r);
	merge(arr,l,m,r);
}
void mergesort(vector<arrtype> &arr)
{
	mergesort(arr,0,arr.size()-1);
}

//usage
int main()
{
	//given an array of size n, sort it
	int n; cin >> n;
	vector<arrtype> arr(n);
	for (int i = 0; i < n; ++i)
		cin >> arr[i];

	mergesort(arr);
	for (auto &a : arr)
		cout << a << ' ';
	cout << '\n';
}
