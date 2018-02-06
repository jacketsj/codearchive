#include <bits/stdc++.h>
using namespace std;

vector<vector<bool>> l2m(vector<vector<int>> adj)
{
	int n = adj.size();
	vector<vector<bool>> m; m.resize(n);
	for (auto &v : m)
		v.resize(n);
	for (int i = 0; i < n; ++i)
		for (auto a : adj[i])
			m[i][a] = true;
	return m;
}
vector<vector<int>> rev(const vector<vector<int>> &adj)
{
	vector<vector<int>> radj; radj.resize(adj.size());
	for (int i = 0; i < adj.size(); ++i)
		for (int a : adj[i])
			radj[a].push_back(i);
	return radj;
}
struct fl
{
	double c, f; //capacity, flow
	fl(double c) : c(c), f(0) {}
};
struct graph
{
	vector<vector<bool>> m;
	vector<vector<int>> adj;
	vector<vector<int>> radj;
	vector<vector<fl>> adjfm;
	vector<double> vcap;
	vector<int> heights;
	//relabel-to-front specific now
	vector<int> currentn;
	vector<vector<int>> ladj; //adjacent and of lower height and flow not capped
	vector<int> currentcount;
	graph(vector<vector<double>> caps,vector<vector<int>> adj) : m(l2m(adj)), adj(adj), radj(rev(adj))
	{
		for (auto &cs : caps)
		{
			vector<fl> a;
			for (auto &c : cs)
			{
				a.push_back(fl(c));
			}
			adjfm.push_back(a);
			vcap.push_back(0);
			heights.push_back(0);
			currentn.push_back(0);
			currentcount.push_back(0);
			ladj.push_back(vector<int>());
		}
	}
	int n()
	{
		return m.size();
	}
	double& cv(int u)
	{
		return vcap[u];
	}
	fl& ce(int u, int v)
	{
		return adjfm[u][v];
	}
	vector<bool>::reference e(int u, int v)
	{
		return m[u][v];
	}
	int& h(int u)
	{
		return heights[u];
	}
	vector<int>& a(int u)
	{
		return adj[u];
	}
	vector<int>& ra(int u)
	{
		return radj[u];
	}
	void push(int u, int v)
	{
		double df = min(cv(u),e(u,v) ? (ce(u,v).c-ce(u,v).f) : (ce(v,u).f));
		if (e(u,v))
			ce(u,v).f += df;
		else
			ce(v,u).f -= df;
		cv(u)-=df; cv(v)+=df;
		cout << "Pushing " << df << " on " << u << "->" << v << '\n';
	}

	bool admisscap(int u, int v)
	{
		if (e(u,v))
			return ce(u,v).c-ce(u,v).f > 0;
		return ce(v,u).f > 0;
	}
	bool admiss(int u, int v)
	{
		//cout << "Checking admission: " << u << "->" << v << '\n';
		return admisscap(u,v) && h(u)>h(v);
	}
	void reladj(int u)
	{
		ladj[u].clear();
		for (int v : adj[u])
			if (admiss(u,v))
				ladj[u].push_back(v);
		for (int v : radj[u])
			if (admiss(u,v))
				ladj[u].push_back(v);
		currentn[u] = 0;
		currentcount[u] = ladj[u].size();
	}
	void relabel(int u)
	{
		int minh = h(u);
		bool first = true;
		for (int v : a(u))
			if (admisscap(u,v))
			{
				if (first)
				{
					first = false;
					minh = h(v);
				}
				minh = min(minh, h(v));
				cout << "    Relabel: " << u << " adj to " << v << "=" << h(v) << '\n';
			}
		for (int v : ra(u))
			if (admisscap(u,v))
			{
				if (first)
				{
					first = false;
					minh = h(v);
				}
				minh = min(minh, h(v));
				cout << "    Relabel: " << u << " adj to " << v << "=" << h(v) << '\n';
			}
		h(u) = 1+minh;
		reladj(u);
		cout << "Relabelling: u=" << u << " : " << h(u) << '\n';
	}

	void initprefl(int s)
	{
		for (int i = 0; i < n(); ++i)
		{
			h(i) = 0;
			cv(i) = 0;
		}
		for (int u = 0; u < n(); ++u)
			for (auto v : a(u))
				ce(u,v).f=0;
	
		h(s) = n();
		for (auto v : a(s))
		{
			ce(s,v).f = ce(s,v).c;
			cv(v) += ce(s,v).c;
			cv(s) -= ce(s,v).c;
		}
		for (int i = 0; i < n(); ++i)
			reladj(i);
	}
	void discharge(int u)
	{
		cout << "Discharging: u=" << u << '\n';
		while (cv(u) > 0)
		{
			
			if (currentn[u] == currentcount[u])
			{
				relabel(u);
				if (currentcount[u] == 0)
					break;
			}
			else
			{
				int v = ladj[u][currentn[u]];
				if (admiss(u,v))
					push(u,v);
				else
					++currentn[u];
			}
		}
	}
	void maxflow(int s, int t) //relabel-to-front
	{
		if (s == t)
			return;
		initprefl(s);
		vector<int> L; //LL, -1 is tail, index is key
		int k = 0;
		for (int i = 0; i < n(); ++i)
			L.push_back(i);
		while (L[s] == t || L[s] == s)
			++L[s];
		while (L[t] == s || L[t] == t)
			++L[t];
		for (int i = 0; i < n()-1; ++i)
			L[i] = L[i+1];
		L[n()-1] = -1;
		int head = 0; //index of head
		while (head == s || head == t)
			++head;
		auto u = head;
		int p = -1;
		while (u != -1)
		{
			int oh = h(u);
			discharge(u);
			if (h(u)>oh)
			{
				if (p >= 0)
				{
					L[p] = L[u];
				}
				if (u != head)
				{
					L[u] = head;
					head = u;
				}
			}
			p = u;
			u = L[u];
		}
	}
};

//usage
int main()
{
	int n = 6;
	vector<vector<int>> adj; adj.resize(n);
	adj[0].push_back(1);
	adj[0].push_back(2);
	adj[0].push_back(5);
	adj[1].push_back(3);
	adj[2].push_back(3);
	adj[1].push_back(2);
	adj[2].push_back(4);
	adj[4].push_back(1);
	adj[4].push_back(3);
	adj[5].push_back(4);
	vector<vector<double>> caps; caps.resize(n);
	for (vector<double> &v : caps)
		v.resize(n);
	caps[0][1] = 4;
	caps[0][2] = 3;
	caps[0][5] = 3;
	caps[1][3] = 3;
	caps[2][3] = 3;
	caps[1][2] = 1;
	caps[2][4] = 4;
	caps[4][1] = 5;
	caps[4][3] = 3;
	caps[5][4] = 2;
	graph g(caps,adj);
	g.maxflow(0,3);
	cout << "Max flow of graph1=" << g.cv(3) << '\n'; //should be 9 in this case
	for (int i = 0; i < n; ++i)
		for (int a : adj[i])
			cout << "    Edge (" << i << ',' << a << ")=" << g.ce(i,a).f << '/' << g.ce(i,a).c << '\n';
	for (int i = 0; i < n; ++i)
		cout << "    Vertex " << i << "=" << g.cv(i) << '\n';


	vector<vector<int>> adj2; adj2.resize(n);
	adj2[0].push_back(2);
	adj2[0].push_back(1);
	adj2[1].push_back(2);
	adj2[2].push_back(1);
	adj2[5].push_back(3);
	adj[3].push_back(5);
	vector<vector<double>> caps2; caps2.resize(n);
	for (vector<double> &v : caps2)
		v.resize(n);
	caps2[0][2] = 1;
	caps2[0][1] = 2;
	caps2[1][2] = 1;
	caps2[2][1] = 1;
	caps2[5][3] = 3;
	caps[3][5] = 3;
	graph g2(caps2,adj2);
	g2.maxflow(0,2);
	cout << "Max flow of graph2=" << g2.cv(2) << '\n'; //should be 2 in this case
	for (int i = 0; i < n; ++i)
		for (int a : adj2[i])
			cout << "    Edge (" << i << ',' << a << ")=" << g2.ce(i,a).f << '/' << g2.ce(i,a).c << '\n';
	for (int i = 0; i < n; ++i)
		cout << "    Vertex " << i << "=" << g2.cv(i) << '\n';
}
