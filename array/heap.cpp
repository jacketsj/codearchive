#include <bits/stdc++.h>
using namespace std;

#define heaptype int
bool cmp(heaptype a, heaptype b)
{
	return a<b; //replace with b<a for max heap
}
struct heap
{
	vector<heaptype> arr; //content
	heap() {}
	static int parent(int i)
	{
		return i/2;
	}
	static int lchild(int i)
	{
		return 2*i+1;
	}
	static int rchild(int i)
	{
		return 2*i+2;
	}
	bool empty()
	{
		return arr.empty();
	}
	void swap_up(int i)
	{
		while(i > 0 && cmp(arr[i],arr[parent(i)]))
		{
			swap(arr[parent(i)],arr[i]);
			i = parent(i);
		}
	}
	void swap_down(int i)
	{
		while (lchild(i) < arr.size())
		{
			if (!cmp(arr[lchild(i)],arr[i]) //i is top or >=
				&& (rchild(i) >= arr.size()
					|| !cmp(arr[rchild(i)],arr[i])))
				break;
			if (cmp(arr[lchild(i)],arr[i]) //l is top
				&& (rchild(i) >= arr.size()
					|| cmp(arr[lchild(i)],arr[rchild(i)])))
			{
				swap(arr[i],arr[lchild(i)]);
				i = lchild(i);
			}
			else //r is top
			{
				swap(arr[i],arr[rchild(i)]);
				i = rchild(i);
			}
		}
	}
	heap(vector<heaptype> &given)
	{
		arr = given;
		for (int i = arr.size()/2; i >= 0; --i)
			swap_down(i);
	}
	heaptype pop()
	{
		heaptype ret = arr[0];
		swap(arr[0],arr[arr.size()-1]);
		arr.pop_back();
		swap_down(0);
		return ret;
	}
	void insert(heaptype n)
	{
		arr.push_back(n);
		swap_up(arr.size()-1);
	}
};

//usage
int main()
{
	//take in sequence of n integers and pop them in reverse order (this is heapsort)
	int n; cin >> n;
	heap h;
	vector<int> arr(n);
	for (int i = 0; i < n; ++i)
	{
		int a; cin >> a;
		h.insert(a);
		arr[i] = a;
	}
	while (!h.empty())
		cout << h.pop() << ' ';
	cout << '\n';
	heap k(arr);
	while (!k.empty())
		cout << k.pop() << ' ';
	cout << '\n';
}
