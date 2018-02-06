#include <bits/stdc++.h>
using namespace std;

#define kt int //key type
#define vt string //value type

vt fail = "fail";

struct avl
{
	kt key;
	vt value;
	avl *l, *r;
	int h; //height
	int c; //number of nodes in tree
	avl(kt key, vt value) : key(key), value(value), l(NULL), r(NULL), h(0) {}
	static int count(const avl* a)
	{
		if (a == NULL)
			return 0;
		return a->c;
	}
	static int height(const avl* a)
	{
		if (a == NULL)
			return -1;
		return a->h;
	}
	bool balance() const
	{
		return height(r) - height(l);
	}
	static void rotL(avl* &a)
	{
		avl* rc = a->r;
		a->r = rc->l;
		rc->l = a;
		a = rc;
	}
	static void rotR(avl* &a)
	{
		avl* lc = a->l;
		a->l = lc->r;
		lc->r = a;
		a = lc;
	}
	static void rotLR(avl* &a)
	{
		rotL(a->r);
		rotR(a);
	}
	static void rotRL(avl* &a)
	{
		rotR(a->l);
		rotL(a);
	}
	static void selfbalance(avl* &a, avl* heavy)
	{
		if (a == NULL)
			return;
		a->h = max(height(a->l),height(a->r));
		a->c = count(a->l) + count(a->r);
		if (heavy == a->r && a->balance() > 1)
		{
			if (heavy->balance() >= 0)
				rotL(a);
			else
				rotRL(a);
		}
		else if (heavy == a->l && a->balance() < 1)
		{
			if (heavy->balance() <= 0)
				rotR(a);
			else
				rotLR(a);
		}
	}
	//operator[] - kth elem
	//operator() - key to value (lookup)
	static void insert(avl* &a, kt key, vt value)
	{
		if (a == NULL)
		{
			a = new avl(key, value);
			return;
		}
		if (key <= a->key)
		{
			insert(a->l, key, value);
			selfbalance(a, a->l);
		}
		else
		{
			insert(a->r, key, value);
			selfbalance(a, a->r);
		}
	}
	static void remove(avl* &a, kt key)
	{
		if (a == NULL)
			return;
		if (key == a->key)
		{
			delete a;
			a = NULL;
		}
		else if (key < a->key)
		{
			remove(a->l, key);
			selfbalance(a, a->r);
		}
		else
		{
			remove(a->r, key);
			selfbalance(a, a->l);
		}
	}
	static vt& find(avl* &a, kt key)
	{
		if (a == NULL)
			//return 0;
			//return vt();
			return fail;
		if (key == a->key)
			return a->value;
		if (key < a->key)
			return find(a->l, key);
		else
			return find(a->r, key);
	}
	//TODO fix
	static vt& get(avl* &a, int i) //order statistics
	{
		if (a == NULL || i < 0 || i >= a->c) //out of bounds
			//return 0;
			//return vt();
			return fail;
		int lc = count(a->l);
		if (i == lc)
			return a->value;
		else if (i < lc)
			return get(a->l,i);
		else
			return get(a->r,i-lc-1);
	}
};
struct avlt
{
	avl* root;
	avlt() : root(NULL) {}
	//operator[] - kth elem
	//operator() - key to value (lookup)
	void insert(kt key, vt value)
	{
		avl::insert(root,key,value);
	}
	void remove(kt key)
	{
		avl::remove(root,key);
	}
	vt& find(kt key)
	{
		return avl::find(root,key);
	}
	vt& get(int i)
	{
		return avl::get(root,i);
	}
	vt& operator()(kt key)
	{
		return find(key);
	}
	vt& operator[](int i)
	{
		return get(i);
	}

};

//usage
int main()
{
	vector<int> testkeys = {1, 2, 3, 4, 0, -1, -2, -3, -6, -4, -3};
	vector<string> testvals = {"1", "2", "3", "4", "0", "-1", "-2", "-3", "-6", "-4", "-3"};
	int n = testkeys.size();
	assert(n == testvals.size());
	avlt t;
	for (int i = 0; i < n; ++i)
		t.insert(testkeys[i],testvals[i]);
	for (int i = n-1; i >= 0; --i)
		cout << "testkey[" << testkeys[i] << "]=" << t(testkeys[i]) << '\n';
	for (int k = -2; k <= n; ++k)
		cout << "the " << k << "-indexed value is " << t[k] << '\n';
}
