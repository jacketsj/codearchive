#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// T is stored type, A is action
// T + A should exist (lazy push function)
// T + T should exist (combine function)
template<typename T, typename A> struct segtree
{
	segtree<T> *l, *r;
	ll bl, br; // range is [bl,br)
	T val;
	A lazy; // lazy already applied to val, but not to subtrees
	template<typename T>
	segtree(ll bl, ll br) : l(NULL), r(NULL), bl(bl), br(br), val(), lazy() {}
	void push()
	{
		if (bl < br - 1) // range is non-trivial
		{
			ll md = (bl + br) / 2;
			if (l == NULL)
				l = new segtree<T,A>(bl,md);
			if (r == NULL)
				r = new segtree<T,A>(md,br);
			l->val = l->val + lazy;
			r->val = r->val + lazy;
			l->lazy = l->lazy + lazy;
			r->lazy = r->lazy + lazy;
			val = l->val + r->val;
		}
		lazy = A(); // clear lazy
	}
	void add(A a, ll ql, ll qr) // query [ql,qr)
	{
		if (qr <= bl || br <= ql)
			return;
		push();
		if (bl <= ql && qr <= br)
			val = val + a;
		else
		{
			l->add(a,ql,qr);
			r->add(a,ql,qr);
		}
	}
	T query(ll ql, ll qr)
	{
		if (qr <= bl || br <= ql)
			return T();
		push();
		if (bl <= ql && qr <= br)
			return val;
		else
			return l->query(ql,qr) + r->query(ql,qr);
	}
};


int main()
{
	ios::sync_with_stdio(0);
	cin.tie(NULL);
}
