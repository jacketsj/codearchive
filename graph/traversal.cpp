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

void dfs(int start, const vector<vector<int>> &adj, void (*visit)(int))
{
	int n = adj.size();
	vector<bool> visited; visited.resize(n);
	stack<int> to_visit;
	to_visit.push(start);
	while (!to_visit.empty())
	{
		int k = to_visit.top(); to_visit.pop();
		if (visited[k])
			continue;
		visited[k] = true;
		visit(k);
		for (int a : adj[k])
			to_visit.push(a);
	}
}

void bfs(int start, const vector<vector<int>> &adj, void (*visit)(int))
{
	int n = adj.size();
	vector<bool> visited; visited.resize(n);
	queue<int> to_visit;
	to_visit.push(start);
	while (!to_visit.empty())
	{
		int k = to_visit.front(); to_visit.pop();
		if (visited[k])
			continue;
		visited[k] = true;
		visit(k);
		for (int a : adj[k])
			to_visit.push(a);
	}
}

struct d_compare
{
	bool operator()(const pair<int,int> &a, const pair<int,int> &b)
	{
		return a.second < b.second;
	}
};
vector<int> dijkstra(int start, const vector<vector<int>> &adj, const vector<vector<int>> &pri, void (*visit)(int))
{
	int n = adj.size();
	vector<bool> visited; visited.resize(n);
	vector<int> dist; dist.resize(n);
	priority_queue<pair<int,int>,vector<pair<int,int>>,d_compare> to_visit;
	to_visit.push(pair<int,int>(start,0));
	while (!to_visit.empty())
	{
		pair<int,int> k = to_visit.top(); to_visit.pop();
		int k0 = k.first;
		if (visited[k0])
		{
			dist[k0] = min(dist[k0],k.second);
			continue;
		}
		visited[k0] = true;
		dist[k0] = k.second;
		visit(k0);

		for (int i = 0; i < adj[k0].size(); ++i)
			to_visit.push(pair<int,int>(adj[k0][i],pri[k0][i]+k.second));
	}
	return dist;
}
vector<int> dijkstra2(int start, const vector<vector<int>> &adj, const vector<vector<int>> &pri)
{
	return dijkstra(start, adj, pri, [](int i) {});
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

	//toposort
	vector<int> order = toposort(adj);
	cout << "Topological ordering: ";
	for (auto a : order)
		cout << a << ' ';
	cout << '\n';
	//now make it a more typical graph
	adj[2].push_back(4);
	adj[5].push_back(1);

	//bfs
	cout << "BFS: ";
	bfs(3, adj, [](int i) { cout << i << ' '; });
	cout << '\n';

	//dfs
	cout << "DFS: ";
	dfs(3, adj, [](int i) { cout << i << ' '; });
	cout << '\n';

	//dijkstra
	int n2 = 5;
	vector<vector<int>> adj2, pri2; adj2.resize(n2); pri2.resize(n2);
	adj2[0].push_back(1); pri2[0].push_back(1); //e.g. shortest path 0->4
	adj2[1].push_back(2); pri2[1].push_back(2);
	adj2[2].push_back(4); pri2[2].push_back(1); //end e.g.
	adj2[0].push_back(3); pri2[0].push_back(4); //e.g. slower (but fewer edge) path 0->4
	adj2[3].push_back(4); pri2[3].push_back(5); //end e.g.
	adj2[2].push_back(0); pri2[2].push_back(0); //cycle-inducing edge
	vector<int> dist = dijkstra2(0, adj2, pri2);
	cout << "Dijstra:\n";
	for (int i = 0; i < n2; ++i)
	{
		cout << "    dist from 0 to " << i << " = " << dist[i] << '\n';
	}
}
