#include <bits/stdc++.h>
using namespace std;

vector<int> kmprecomp(const string &m)
{
	vector<int> ret(m.size()+1);
	int btloc = 0;
	//amortized linear time for arbitrarily sized alphabets
	for (int i = 2; i <= m.size(); ++i)
	{
		//loop invariant: m[0..btloc] matches m[i-btloc...i], with 1-based indexing
		while (btloc > 0) //while something was matched
		{
			if (m[btloc] == m[i-1]) //if it still matches
				break;
			btloc = ret[btloc]; //go to next smallest matching prefix
		}
		if (m[btloc] == m[i-1]) //go forward if the new match succeeded
			++btloc;
		ret[i] = btloc;
	}
	return ret;
}

vector<int> kmp(const string &s, const string &m)
{
	vector<int> fedge=kmprecomp(m); //success edge and fail edge in dfa, index is number of characters matched
	int loc=0;
	vector<int> ret;
	//amortized linear time for arbitrarily sized alphabets
	for (int i = 0; i < s.size(); ++i)
	{
		auto c = s[i];
		while (loc > 0 && c != m[loc])
			loc = fedge[loc];
		if (c == m[loc])
			++loc;
		if (loc == m.size())
		{
			ret.push_back(i-m.size()+1); //add location of string
			loc = fedge[loc]; //go to f-edge for entire string
		}
	}
	return ret;
}

//usage
int main()
{
	//take in two strings: a string s, and a string m, output the points at which m is inside s
	cout << "Need: a string s and a match string m" << endl;
	string s, m; cin >> s >> m;
	vector<int> locs = kmp(s, m);

	cout << s << '\n';
	//print aligned positions of matches
	int l = 0;
	for (auto i : locs)
	{
		while (l < i)
		{
			cout << ' ';
			++l;
		}
		cout << '|';
		++l;
	}
	cout << '\n';
}
