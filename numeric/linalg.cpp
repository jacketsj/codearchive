#include <bits/stdc++.h>
using namespace std;

#define eps 1e-9 //epsilon
typedef long double ld;

struct vpt
{
	int d;
	vector<ld> v;
	vpt(int d) : d(d), v(d) {}
	vpt(int d, vector<ld> v) : d(d), v(v)
	{
		assert(d==v.size());
	}
	vpt(const vpt &og) : d(og.d), v(og.v) {}
	void operator=(const vpt &og)
	{
		d = og.d;
		v = og.v;
	}
	bool operator==(vpt &o)
	{
		if (d != o.d)
			return false;
		for (int i = 0; i < d; ++i)
			if (abs(p(i)-o.p(i)) > eps)
				return false;
		return true;
	}
	void print()
	{
		for (int i = 0; i < d; ++i)
			cout << p(i) << ' ';
		cout << '\n';
	}
	ld& p(int dd)
	{
		return v[dd];
	}
	void operator*=(ld &m)
	{
		for (auto &elem : v)
			elem *= m;
	}
	vpt operator*(ld &m)
	{
		vpt ret(*this);
		ret*=m;
		return ret;
	}
	vpt operator+(vpt &o)
	{
		assert(d==o.d);
		vpt ret(*this);
		for (int i = 0; i < d; ++i)
			ret.p(i) += o.p(i);
		return ret;
	}
	static vpt e(int d, int dd)
	{
		vpt ret(d);
		ret.p(dd) = 1;
		return ret;
	}
};

struct mtr
{
	int d;
	vector<ld> v;
	mtr(int d) : d(d), v(d*d) {}
	mtr(const mtr &og) : d(og.d), v(og.v) {}
	void operator=(const mtr &og)
	{
		d = og.d;
		v = og.v;
	}
	ld& p(int x, int y)
	{
		return v[d*y+x];
	}
	bool operator==(mtr &o)
	{
		if (d != o.d)
			return false;
		for (int i = 0; i < d; ++i)
			for (int j = 0; j < d; ++j)
				if (abs(p(i,j)-o.p(i,j)) > eps)
					return false;
		return true;
	}
	void print()
	{
		for (int x = 0; x < d; ++x)
		{
			for (int y = 0; y < d; ++y)
				cout << p(x,y) << ' ';
			cout << '\n';
		}
	}
	void operator*=(ld &m)
	{
		for (auto &elem : v)
			elem *= m;
	}
	mtr operator*(ld &m)
	{
		mtr ret(*this);
		ret*=m;
		return ret;
	}
	vpt operator*(vpt &vo)
	{
		vpt ret(d);
		for (int y = 0; y < d; ++y)
			for (int x = 0; x < d; ++x)
				ret.p(y) += vo.p(x)*p(x,y);
		return ret;
	}
	mtr operator*(mtr &o)
	{
		assert(d==o.d);
		mtr ret(d);
		for (int x = 0; x < d; ++x)
			for (int y = 0; y < d; ++y)
				for (int i = 0; i < d; ++i)
					ret.p(x,y) += p(i,y)*o.p(x,i);
		return ret;
	}
	mtr operator+(mtr &o)
	{
		assert(d==o.d);
		mtr ret(*this);
		for (int i = 0; i < d; ++i)
			for (int j = 0; j < d; ++j)
				ret.p(i,j) += o.p(i,j);
		return ret;
	}
	static mtr i(int d)
	{
		mtr ret(d);
		for (int i = 0; i < d; ++i)
			ret.p(i,i) = 1;
		return ret;
	}
	//specific code for generating rotation transforms
	static mtr rot(int d, int off, ld theta) //off is dimension offset
	{
		mtr ret = i(d);
		ld st = sin(theta), ct = cos(theta);
		ret.p(off,off) = ct;
		ret.p((off+1)%d,off) = -st;
		ret.p(off,(off+1)%d) = st;
		ret.p((off+1)%d,(off+1)%d) = ct;
		return ret;
	}
};

//usage
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(NULL);

	ld p = 0, y = M_PI/3, r = 0; //pitch, yaw, roll
	//generate rotation matrix for these dimensions
	mtr R0[] = {mtr::rot(3,0,p),mtr::rot(3,1,y),mtr::rot(3,2,r)};
	mtr R = R0[0]*R0[1];
	R = R*R0[2];
	//generate the coordinates for a cube with side lengths of 1
	vector<vpt> cube;
	for (ld i = -0.5; i < 1.5; i += 1)
		for (ld j = -0.5; j < 1.5; j += 1)
			for (ld k = -0.5; k < 1.5; k += 1)
				cube.push_back(vpt(3,vector<ld>{i,j,k}));
	//transform the coordinates with the matrix
	for (auto &pp : cube)
		pp = R*pp;
	//project the points onto the x-y plane
	vector<vpt> points;
	for (auto &v : cube)
		points.push_back(vpt(2,vector<ld>{v.p(0),v.p(1)}));
	for (auto &v : points)
		v.print();
}
