#include <bits/stdc++.h>
using namespace std;

#define AL 26
#define ze 'a'

struct trie
{
	bool acc;
	int from;
	trie *c[AL];
	trie() : acc(false), from(-1)
	{
		for (int i = 0; i < AL; ++i)
			c[i] = NULL;
	}
};

void tadd(trie &t, string &s, int from)
{
	trie *cur = &t;
	for (int i = 0; i < s.length(); ++i)
	{
		if (cur->c[s[i]-ze] == NULL)
			cur->c[s[i]-ze] = new trie();
		cur = cur->c[s[i]-ze];
	}
	cur->acc = true;
	cur->from = from;
}


//usage
int main()
{
	//given n strings that can be matched (put in the trie), determine from which strings a string s is a concatenation
	//must assume that no match string is a prefix of another, otherwise must use non-determinism (slower by a factor of n)
	int n; cin >> n;
	trie mt;
	vector<string> matches;
	for (int i = 0; i < n; ++i)
	{
		string m; cin >> m;
		matches.push_back(m);
		tadd(mt, matches[i], i); //store matches[i] with i as an index in input
	}
	string m; cin >> m;
	trie *cur = &mt;
	vector<int> seen; //which indexes we've seen
	for (auto &ch : m)
	{
		cur = cur->c[ch-ze];
		if (cur->acc) //finished a word
		{
			seen.push_back(cur->from); //push origin index
			cur = &mt;
		}
	}
	for (auto i : seen) //indeces we've seen
		cout << matches[i] << ' ';
	cout << '\n';
}
