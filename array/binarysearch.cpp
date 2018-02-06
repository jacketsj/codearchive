#include <bits/stdc++.h>
using namespace std;
#define bstype double

vector<int> arr; //ignore, demonstration

//assumes 'large' is a monotonic cutoff
bstype binarysearch(bstype l, bstype r, bool (*large)(bstype), bstype epsilon)
{
	bstype m = (l+r)/2;
	while (r-l>epsilon)
	{
		if (large(m))
			r = m;
		else
			l = m;
		m = (l+r)/2;
	}
	return m;
}

//usage
int main()
{
	//e.g. find sqrt(2) without newton's method
	cout << "sqrt(2)=" << binarysearch(1,2,[](bstype k){return k*k>2;},1e-8) << '\n';
	//e.g. search sorted array for index containing 8
	arr = {1, 2, 4, 5, 8, 10, 11, 12}; //(index is 4)
	cout << "arr^(-1)[8]="
		<< int(binarysearch(0, arr.size(), [](bstype k){return arr[int(k)] > 8;},4e-1)) << '\n';
}
