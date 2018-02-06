#include <bits/stdc++.h>
using namespace std;

vector<int> sieve(int n)
{
	vector<bool> v; v.resize(n+1);
	for (int i = 2; i*i <= n; ++i)
		if (!v[i])
			for (int j = i*i; j <= n; j += i) //j is a multiple of i
				v[j] = true;
	vector<int> ret;
	for (int i = 2; i <= n; ++i)
		if (!v[i])
			ret.push_back(i);
	return ret;
}

//suage
int main()
{
	int n = 100;
	vector<int> primes = sieve(n);
	cout << "Primes under " << n << ": ";
	for (auto p : primes)
		cout << p << ',';
	cout << '\n';
}
