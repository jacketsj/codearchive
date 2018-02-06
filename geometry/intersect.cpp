#include <bits/stdc++.h>
using namespace std;

struct pt
{
	double x, y;
	pt(double x, double y) : x(x), y(y) {}
};

struct linseg
{
	pt a, b;
	linseg(pt a, pt b) : a(a), b(b) {}
	linseg(double x1, double y1, double x2, double y2) : a(pt(x1,y1)), b(pt(x2,y2)) {}
	bool isectray(const linseg &o) const
	{
		return ((b.x-a.x)*(o.a.y-b.y)-(b.y-a.y)*(o.a.x-b.x))
			* ((b.x-a.x)*(o.b.y-b.y)-(b.y-a.y)*(o.b.x-b.x))
			< 0;
	}
	bool isect(const linseg &o) const
	{
		return isectray(o) && o.isectray(*this);
	}
};

//usage
string prt(pt a)
{
	return "(" + to_string(a.x) + "," + to_string(a.y) + ")";
}
string prt(linseg a)
{
	return prt(a.a) + "-" + prt(a.b);
}
int main()
{
	pt a(0,0), b(4,0), c(-1,2), d(4,-2), e(2,3), f(7,-1);
	linseg ls1(a,b), ls2(c,d), ls3(e,f);
	cout << "Lines " << prt(ls1) << " and " << prt(ls2) << " instersect: " << ls1.isect(ls2) << '\n';
	cout << "Lines " << prt(ls1) << " and " << prt(ls3) << " instersect: " << ls1.isect(ls3) << '\n';
}
