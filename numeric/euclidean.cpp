#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b)
{
	int t;
	while (b > 0)
	{
		t = b;
		b = a % b;
		a = t;
	}
	return a;
}

int lcm(int a, int b)
{
	return a*b/gcd(a,b);
}

int modinv(int a, int n)
{
	int t = 0, t0 = 1, r = n, r0 = a, q, temp;
	while (r0 != 0)
	{
		q = r / r0;
		temp = t;
		t = t0;
		t0 = temp - q*t0;
		temp = r;
		r = r0;
		r0 = temp - q*r0;
	}
	if (r > 1)
		return -1; //not invertible
	return (t+n)%n;
}

//usage
int main()
{
	srand(time(NULL));
	int cap = 300;
	int a(rand()%cap), b(rand()%cap);

	cout << "gcd(" << a << ',' << b << ")=" << gcd(a,b) << '\n';
	cout << "lcm(" << a << ',' << b << ")=" << lcm(a,b) << '\n';
	int r = modinv(a%b,b);
	if (r == -1)
		cout <<  a%b << "mod" << b << " is not invertible.\n";
	else
		cout <<  a%b << "^(-1)mod" << b << "=" << r << '\n';
}
