//solution for "bonuses" in https://lpc.ucfprogrammingteam.org/localFiles/local2018Problems.pdf
#include <bits/stdc++.h>
using namespace std;

//based on https://codeforces.com/blog/entry/18051
struct segtree
{
	int n;
	vector<unsigned long long> t;
	segtree(int n) : n(n), t(2*n)
	{
		/*
		//round n up to closest power of 2
		//not necessary in most cases, might be helpful for some easier operation extensions
		int i = 0;
		while (n > 0)
		{
			n /= 2;
			++i;
		}
		this->n = n = 1 << (i);
		t.resize(2*n);
		*/
	}
	//do a range update on [l,r)
	void modify(int l, int r, unsigned long long val)
	{
		for (l += n, r += n; l < r; l >>= 1, r >>= 1)
		{
			if (l&1) t[l++] += val;
			if (r&1) t[--r] += val;
		}
	}
	unsigned long long query(int p)
	{
		p += n;
		//find largest significant digit of p
		int s = 0;
		while ((p >> s) > 0)
				++s;
		--s;
		//go down the seg-tree to the last parent, pushing the results down
		for (; s > 0; --s)
		{
			int cur = p>>s;
			t[2*cur] += t[cur];
			t[2*cur+1] += t[cur];
			t[cur] = 0;
		}
		//clear in-tree values for this node
		unsigned long long res = t[p];
		t[p] = 0;
		return res;
	}
	/*
	//do a fancy print for debugging purposes
	void print()
	{
		cout << "tree:" << endl;;
		vector<int> sizes(2*n);
		int c = 1;
		for (int k = n; k > 0; k >>= 1) //for each level
		{
			for (int i = 0; i < c; ++i)
			{
				string val = "|" + to_string(t[c+i]);
				while (val.size() < 5*k)
					val += ' ';
				cout << val;
			}
			cout << "|\n";
			c *= 2;
		}
	}
	*/
};

void pre_trav(vector<vector<int>> &children, vector<int> &euler, vector<int> &max_sub, int i, int &count)
{
	euler[i] = count++;
	for (int c : children[i])
	{
		pre_trav(children,euler,max_sub,c,count);
	}
	max_sub[i] = count;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(NULL);

	int N, S; cin >> N >> S;
	int n = 1;
	vector<vector<int>> children(1);
	vector<int> types(N);
	vector<int> indeces(N);
	vector<unsigned long long> params(N);
	for (int NN = 0; NN < N; ++NN)
	{
		vector<int> push_me;
		int type, i; cin >> type >> i; --i;
		int param = 0;
		switch (type)
		{
			case 1:
				children.push_back(push_me);
				types[NN] = 2;
				indeces[NN] = n;
				params[NN] = S;
				children[i].push_back(n++);
				break;
			case 2:
				cin >> param;
				types[NN] = type;
				indeces[NN] = i;
				params[NN] = param;
				break;
			case 3:
				cin >> param;
				types[NN] = type;
				indeces[NN] = i;
				params[NN] = param;
				break;
			default:
				types[NN] = type;
				indeces[NN] = i;
				params[NN] = param;
		}
	}
	vector<int> euler(n), range(n); //what are the order of the nodes, what are the indeces of the nodes' range
	int count = 0;
	pre_trav(children,euler,range,0,count);
	vector<unsigned long long> mult(n);
	vector<unsigned long long> money(n);
	mult[0] = S; //CEO starts with multiplier S
	//initialize the segtree with the number of nodes in the tree
	segtree seg(n);
	for (int NN = 0; NN < N; ++NN)
	{
		int type = types[NN];
		int i = indeces[NN];
		unsigned long long param = params[NN];
		unsigned long long val = 0;
		switch (type)
		{
			case 2:
				//update non-segtree state so that the mult paramter can be changed
				val = seg.query(euler[i]);
				money[i] += mult[i] * val;
				mult[i] = param;
				break;
			case 3:
				//do a range update
				seg.modify(euler[i],range[i],param);
				break;
			default:
				//update non-segtree state for output
				val = seg.query(euler[i]);
				money[i] += mult[i] * val;
				cout << money[i] << '\n';
		}
	}
}
