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

struct delem
{
	int pos, dist, origin;
	delem(int p, int d, int o) : pos(p), dist(d), origin(o) {}
	bool operator<(const delem &oth) const
	{
		//priority_queue is a max heap
		return oth.dist < dist;
	}
};
vector<int> dijkstra(int start, const vector<vector<int>> &adj, const vector<vector<int>> &pri, void (*visit)(delem))
{
	int n = adj.size();
	vector<bool> visited(n);
	vector<int> dist(n);
	for (int i = 0; i < n; ++i)
		dist[i] = -1; //infinity
	priority_queue<delem> to_visit;
	to_visit.push(delem(start, 0, -1));
	while (!to_visit.empty())
	{
		delem cur = to_visit.top(); to_visit.pop();
		if (visited[cur.pos])
			continue;
		visited[cur.pos] = true;
		dist[cur.pos] = cur.dist;
		visit(cur);
		for (int i = 0; i < adj[cur.pos].size(); ++i)
			to_visit.push(delem(adj[cur.pos][i], cur.dist+pri[cur.pos][i], cur.pos));
	}
	return dist;
}
vector<int> dijkstra2(int start, const vector<vector<int>> &adj, const vector<vector<int>> &pri, void (*visit)(int))
{
	static void (*visitst)(int) = [](int i) {};
	visitst = visit;
	return dijkstra(start, adj, pri, [](delem d) { visitst(d.pos); });
}
vector<int> dijkstra3(int start, const vector<vector<int>> &adj, const vector<vector<int>> &pri)
{
	return dijkstra2(start, adj, pri, [](int i) {});
}
vector<int> dijkstra4(int start, int end, const vector<vector<int>> &adj, const vector<vector<int>> &pri)
{
	static vector<int> *prevst;
	vector<int> prev(adj.size());
	prevst = &prev;
	vector<int> dist = dijkstra(start, adj, pri, [](delem d) { (*prevst)[d.pos] = d.origin; });
	vector<int> path;
	if (dist[end] == -1) //no usable path
		return path;
	int cur = end;
	path.push_back(cur);
	while (cur != start)
	{
		cur = prev[cur];
		path.push_back(cur);
	}
	reverse(path.begin(), path.end());
	return path;
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
	vector<int> dist = dijkstra3(0, adj2, pri2);
	cout << "Dijstra:\n";
	for (int i = 0; i < n2; ++i)
	{
		cout << "    dist from 0 to " << i << " = " << dist[i] << '\n';
	}
	vector<int> path = dijkstra4(0, 4, adj2, pri2);
	cout << "Path from 0 to 4: ";
	for (auto i : path)
		cout << i << ' ';
	cout << '\n';
}
