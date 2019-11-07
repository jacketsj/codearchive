//arbitrary-dimension segtree
//example solves Problem F 'Rectangles' in ICPC PNW Regional 2018 http://acmicpc-pacnw.org/ProblemSet/2018/div1.pdf
//this doesn't work right now, probably hard to fix
#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long param;

//based on https://codeforces.com/blog/entry/18051
// and https://codeforces.com/blog/entry/64914 (for the templating and the map usage)
template <int... ArgsT> struct segtree
{
	param stored = 0;
	void modify(param val)
	{
		//do operation segtree keeps track of
		//stored += val;
		stored = (stored + val) % 2;
	}
	param query()
	{
		return stored;
	}
};

template <int n, int... Ns>
struct segtree<n, Ns...>
{
	map<int,segtree<Ns...>> t; //store of lower dimension trees (extra log factor to save memory, otherwise size here is 2*n)
	//do a range update on [l,r)
	//log^2 N_1 * log^2 N_2 * ... time
	template<typename... Args>
	void modify(int l, int r, Args... args)
	{
		for (l += n, r += n; l < r; l >>= 1, r >>= 1)
		{
			if (l&1)
				t[l++].modify(args...);
			if (r&1)
				t[--r].modify(args...);
		}
	}
	template<typename... Args>
	param query(int l, int r, Args... args)
	{
		auto first = t.lower_bound(l);
		auto last = t.upper_bound(r)++;
		param res = 0;
		for (auto iter = first; iter != last; ++iter)
		{
			int magnitude = 1;
			int k = iter->first;
			while (k < n)
			{
				k *= 2;
				++magnitude;
			}
			res += magnitude * (iter->second).query(args...);
		}
		//int magnitude = 1;
		//for (l += n, r += n; l < r; l >>= 1, r >>= 1)
		//{
		//	if (l&1)
		//	{
		//		cout << "next level\n";
		//		res += magnitude*t[l++].query(args...);
		//		cout << "prev level\n";
		//	}
		//	if (r&1)
		//	{
		//		cout << "next level\n";
		//		res += magnitude*t[--r].query(args...);
		//		cout << "prev level\n";
		//	}
		//	//the result from a sub-segtree at the next height is worth twice as much
		//	// (there are twice as many of them)
		//	magnitude *= 2;
		//}
		//cout << "sum[" << l << "," << r << ")=" << res << endl;
		return res;
	}
};

#define N 1000000007

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(NULL);

	//can do more dimensions than 2, but here we only need 2
	segtree<N,N> seg;
	int n; cin >> n;
	for (int i = 0; i < n; ++i)
	{
		int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
		seg.modify(x1,x2,y1,y2,1);
	}
	cout << seg.query(0,N,0,N) << endl;
}
