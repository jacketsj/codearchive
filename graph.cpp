#include <bits/stdc++.h>
using namespace std;

vector<int> toposort(vector<vector<int>> adj) //adj is modified
{
	int n = adj.size();
	vector<bool> pmarks, tmarks; pmarks.resize(n); tmarks.resize(n);
	vector<int> edgecount; edgecount.resize(n);
	for (vector<int> &ls : adj)
		for (int &c : ls)
			++edgecount[c];
	
	queue<int> S;
	for (int i = 0; i < n; ++i)
		if (edgecount[i] == 0)
			S.push(i);

	vector<int> ret;
	while (!S.empty())
	{
		int l = S.front(); S.pop();
		ret.push_back(l);
		for (int a : adj[l])
			if (--edgecount[a] == 0)
				S.push(a);	
		adj[l].clear();
	}
	for (vector<int> &ls : adj)
		if (!ls.empty())
			return vector<int>(); //cycle detected
	return ret;
}

//usage
int main()
{
	int n = 6;
	vector<vector<int>> adj; adj.resize(n);
	adj[3].push_back(2);
	adj[3].push_back(0);
	adj[4].push_back(1);
	adj[1].push_back(0);
	adj[0].push_back(2);
	adj[0].push_back(5);
	adj[5].push_back(2);
	vector<int> order = toposort(adj);
	cout << "Topological ordering: ";
	for (auto a : order)
		cout << a << ' ';
	cout << '\n';
}
