#include <bits/stdc++.h>
using namespace std;
#define eps 1e-10 //may want to change

struct pt
{
	double x, y;
	pt() {}
	pt(double x, double y) : x(x), y(y) {}
	pt operator+(const pt &o) const
	{
		return pt(x+o.x,y+o.y);
	}
	pt operator-(const pt &o) const
	{
		return pt(x-o.x,y-o.y);
	}
};

pt basis;
inline double p2(double a)
{
	return a*a;
}
bool ang_compare(const pt &a, const pt &b)
{
	
	double det = (b.x-a.x)*(basis.y-a.y) - (basis.x-a.x)*(b.y-a.y);
	if (det-eps > 0)
		return false;
	if (det+eps < 0)
		return true;
	//colinear, can return false if colinearity not wanted
	return p2(basis.x-a.x)+p2(basis.y-a.y) < p2(basis.x-b.x)+p2(basis.y-b.y);
}

vector<int> giftwrap(const vector<pt> &points)
{
	int n = points.size();
	if (n == 0)
		return vector<int>();
	int bot = 0, boty = points[0].y;
	for (int i = 1; i < n; ++i)
	{
		const pt &p = points[i];
		if (p.y < boty)
		{
			bot = i; boty = p.y;
		}
	}
	vector<int> ret; ret.push_back(bot);
	if (n == 1)
		return ret;

	int cur = bot;
	do
	{
		basis = points[cur];
		int next = 0;
		if (0 == cur)
			next = 1;
		for (int i = 1; i < n; ++i)
		{
			if (i == cur)
				continue;	
			if (ang_compare(points[i],points[next]))
				next = i;
		}
		if (next == bot)
			break;
		ret.push_back(next);
		cur = next;
			
	} while (cur != bot);
	return ret;
}

const vector<pt> *gsp;
vector<int> grahamscan(const vector<pt> &points)
{
	gsp = &points;

	int n = points.size();
	if (n == 0)
		return vector<int>();
	int bot = 0, boty = points[0].y;
	for (int i = 1; i < n; ++i)
	{
		const pt &p = points[i];
		if (p.y < boty)
		{
			bot = i; boty = p.y;
		}
	}

	basis = points[bot];
	vector<int> points_s; points_s.resize(n);
	for (int i = 0; i < n; ++i)
		if (i != bot)
			points_s.push_back(i);
	sort(points_s.begin(), points_s.end(),
		[](int a, int b){return ang_compare((*gsp)[a], (*gsp)[b]);} );
	points_s.push_back(bot);
	stack<int> rets;
	rets.push(bot);
	for (int cur : points_s)
	{
		if (rets.size() < 2 && cur != bot)
			rets.push(cur);
		else if (rets.size() >= 2)
		{
			int t1, t2;
			do
			{
				t1 = rets.top(); rets.pop(); t2 = rets.top();
				basis = points[t1];
			} while (rets.size() > 1 && !ang_compare(points[t1]+(points[t1]-points[t2]), points[cur])); //pops previous colinear points
			if (rets.size() > 1 || ang_compare(points[t1]+(points[t1]-points[t2]), points[cur]))
				rets.push(t1);
			if (cur != bot)
				rets.push(cur);
		}
	}

	vector<int> ret;
	while (!rets.empty())
	{
		ret.push_back(rets.top());
		rets.pop();
	}
	return ret;
}

//usage
int main()
{
	vector<pt> points;
	points.push_back(pt(0,0));
	points.push_back(pt(1,0));
	points.push_back(pt(2,0));
	points.push_back(pt(3,0));
	points.push_back(pt(4,0));
	points.push_back(pt(0,1));
	points.push_back(pt(1,2));
	points.push_back(pt(1,1));
	points.push_back(pt(2,2));
	points.push_back(pt(2,1));
	points.push_back(pt(3,1));

	//giftwrap
	vector<int> ch = giftwrap(points);
	cout << "Giftwrap gives convex hull of: ";
	for (int k : ch)
		cout << '(' << points[k].x << ',' << points[k].y << "),";
	cout << '\n';

	//grahamscan
	ch = grahamscan(points);
	cout << "Graham scan gives convex hull of: ";
	for (int k : ch)
		cout << '(' << points[k].x << ',' << points[k].y << "),";
	cout << '\n';
}
