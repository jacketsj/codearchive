#include <bits/stdc++.h>
using namespace std;

#define arrtype int //replace with a struct (that has a comparator) to use key/values
/*
struct arrtype
{
	int key;	
	int val;
	bool operator<(arrtype other)
	{
		return key < other.key;
	}
	bool operator==(arrtype other)
	{
		return key == other.key;
	}
};
*/

//unstable, but inplace
void quicksort(vector<arrtype> &arr, int l, int r)
{
	if (l >= r)
		return;
	swap(arr[(rand()%(r-l+1))+l],arr[l]);
	int k = r;
	for (int i = l+1; i <= k; ++i)
	{
		if (arr[i] < arr[i-1])
			swap(arr[i],arr[i-1]);
		else
			swap(arr[i--],arr[k--]);
	}
	quicksort(arr,l,k-1);
	quicksort(arr,k+1,r);
}
void quicksort(vector<arrtype> &arr)
{
	quicksort(arr,0,arr.size()-1);
}

//usage
int main()
{
	//given an array of size n, sort it
	int n; cin >> n;
	vector<arrtype> arr(n);
	for (int i = 0; i < n; ++i)
		cin >> arr[i];

	quicksort(arr);
	for (auto &a : arr)
		cout << a << ' ';
	cout << '\n';
}
