#include <bits/stdc++.h>
using namespace std;

struct hash_fn //a hash function (for integers)
{
	int M;
	const int w = sizeof(int)*8; // word size for int (in bits not bytes, so *8), i.e. how big are the things we're hashing
	// a is a random odd positive integer less than 2^w (i.e. an integer), b is a random non-negative integer less than 2^(w-M)
	unsigned a, b;
	//generate a universal hash function with 2^M bins
	hash_fn(int M) : M(M)
	{
		a = (unsigned(rand()) << 1) + 1;
		b = unsigned(rand()) >> M;
	}
	//evaluate the hash function
	unsigned operator()(int in)
	{
		return unsigned(a*in+b) >> (w-M);
	}
};

struct bloom_filter
{
	vector<bool> data;
	vector<hash_fn> fns;
	//create an empty bloom filter with an expected n entries, and error rate p=2^-P
	bloom_filter(unsigned n, unsigned P)
	{
		// m=2^M=[-n ln(p)]/[ln(2)]^2=nP/ln(2), M=p^(n/ln(2))=log(nP)-log(log(2))<log(nP)+1<log_2(nP)+1
		// k=(m/n)ln(2)
		unsigned M = 1; //2^M is size of filter
		unsigned nP = unsigned(double(P*n)/M_LN2); // nP/ln(2)
		while (nP >>= 1) // compute log_2(nP)
			M++;
		data.resize(1<<M);
		unsigned k = P; // number of hash functions
		// could use double hashing instead of universal hash functions,
		//   i.e. hash_i = (hash_a(x)+i*hash_b(x)) mod m
		for (unsigned i = 0; i < k; ++i)
			fns.push_back(hash_fn(M));
		cout << "m=" << (1<<M) << ",k=" << k << endl;
	}
	void insert(int elem)
	{
		for (hash_fn f : fns)
			data[f(elem)] = true;
	}
	//may give false positives
	bool check(int elem)
	{
		bool ret = true;
		for (hash_fn f : fns)
			ret &= data[f(elem)];
		return ret;
	}
};


//usage
int main()
{
	srand(0);
	//take in expected number of entries
	cout << "Enter your expected number of entries." << endl;
	int n; cin >> n;
	int P = 6; // want errors with probability at most 2^-6
	bloom_filter filter(n,P);
	string input; 
	do
	{
		cout << "Options: \"exit\" to quit, \"insert [int]\" to insert, \"query [int]\" to query." << endl;
		cin >> input;
		if (input == "insert")
		{
			int val; cin >> val;
			filter.insert(val);
		}
		else if (input == "query")
		{
			int val; cin >> val;
			if (filter.check(val))
				cout << "Possibly in set" << endl;
			else
				cout << "Not in set" << endl;
		}
		else if (input == "testinsert")
		{
			int val; cin >> val;
			int count = 0;
			for (int i = 0; i < val; ++i)
				filter.insert(rand());
		}
		else if (input == "testquery")
		{
			int val; cin >> val;
			int count = 0;
			for (int i = 0; i < val; ++i)
				if (filter.check(rand()))
					++count;
			cout << "count=" << count << " out of val=" << val << " randomly chosen values were hits" << endl;
		}
	} while (input != "exit" && input != "q" && input != "quit");
}
