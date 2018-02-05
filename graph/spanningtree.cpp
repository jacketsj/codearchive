#include <bits/stdc++.h>
using namespace std;

struct dsu //uptree
{
	vector<int> cat;
	//negative is root with count
	dsu(int n)
	{
		for (int i = 0; i < n; ++i)
			cat.push_back(-1);
	}
	int root(int a)
	{
		if (cat[a] < 0)
			return a;
		vector<int> tp;
		while (cat[a] >= 0)
		{
			tp.push_back(a);
			a = cat[a];
		}
		for (auto b : tp)
			cat[b] = a;
		return a;
	}

	bool eq(int a, int b)
	{
		return root(a) == root(b);
	}

	void merge(int a, int b)
	{
		a = root(a);
		b = root(b);
		if (a == b)
			return;
		if (cat[a] < cat[b])
		{
			cat[b] += cat[a];
			cat[a] = b;
		}
		else
		{
			cat[a] += cat[b];
			cat[b] = a;
		}
	}
};

struct edge
{
	int a, b, w; //node 1, node 2, weight
	edge(int a, int b, int w) : a(a), b(b), w(w) {}
};
bool e_compare(const edge &a, const edge &b)
{
	return a.w < b.w;
}
vector<edge> kruskal(vector<edge> edges, int n)
{
	dsu d(n);
	sort(edges.begin(),edges.end(),e_compare);
	vector<edge> mst;
	for (auto &e : edges)
	{
		if (d.eq(e.a,e.b))
			continue;
		d.merge(e.a, e.b);
		mst.push_back(e);
	}
	return mst;
}

//usage
int main()
{
	int n = 5;
	vector<edge> edges;
	edges.push_back(edge(0,2,3));
	edges.push_back(edge(0,3,8));
	edges.push_back(edge(0,4,2));
	edges.push_back(edge(4,2,4));
	edges.push_back(edge(1,4,3));
	edges.push_back(edge(1,2,4));
	vector<edge> mst = kruskal(edges, n);
	cout << "Spanning tree:\n";
	for (auto &e : mst)
		cout << "    " << e.a << '-' << e.b << ':' << e.w << '\n';
}
