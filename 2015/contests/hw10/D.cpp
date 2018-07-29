
#include <bits/stdc++.h>
#include <unordered_map>
#include <initializer_list>
#include <memory>
#include <vector>
#define mp make_pair
#define pb push_back
#define lo int
#define li long long int
#define db double

//#define sz(a) (lo)(a).size()
#define FOR(i, n) for(int i = 0; i < (n); i++)
#define FORN(i, j, n) for(int i = (j); i <(n); i++)
#define all(a) (a).begin(), (a).end()
using namespace std;
#define DEB(...) fprintf(stderr, __VA_ARGS__)
//=======================
//======================

//=======================
//#define pi 3.14159265358979323
#define eps 1e-9
#define INF 2e9
#define MN 3010
#define SM 26
//================================
struct automato
{
	struct leaf
	{
		lo link, len, first, last;
		map<char, lo> nex;
		leaf() {}
	};
	vector<leaf> tree;
	lo sz, pre;
	automato() {
		sz = 1;
		pre = 0;
		tree = vector<leaf>(1);
		tree[0].link = -1;
		tree[0].len = 0;
	}
	void add_s(char c)
	{
		lo cur = sz++;
		tree.push_back(leaf());
		tree[cur].len = tree[pre].len + 1;
		tree[cur].first = tree[cur].len - 1;
		lo temp = pre;
		for (; temp != -1 && !tree[temp].nex.count(c); temp = tree[temp].link)
		{
			tree[temp].nex[c] = cur;
		}
		if (temp == -1)
		{
			tree[cur].link = 0;
		}
		else
		{
			lo p = tree[temp].nex[c];
			if (tree[p].len == tree[temp].len + 1)
			{
				tree[cur].link = p;
			}
			else
			{
				lo clone = sz++;
				tree.pb(leaf());
				tree[clone].nex = tree[p].nex;
				tree[clone].len = tree[temp].len + 1;
				tree[clone].link = tree[p].link;
				tree[clone].first = tree[p].first;
				tree[p].link = clone;
				tree[cur].link = clone;

				for (; temp != -1 && tree[temp].nex.count(c) && tree[temp].nex[c] == p; temp = tree[temp].link)
				{
					tree[temp].nex[c] = clone;
				}
			}
		}
		pre = cur;
	};
	void add_str(char *s)
	{
		lo n = strlen(s);
		FOR(i, n)
		{
			add_s(s[i]);
		}
	}
	lo nx(lo id, char c)
	{
		if (!tree[id].nex.count(c))
			return -1;
		return tree[id].nex[c];
	}
	void dfs(int id, vector<vector<int>> &g){
		for(auto to : g[id]){
			dfs(to, g);
			tree[id].last = max(tree[id].last, tree[to].last);
		}
	}
	int take_last(){
		vector<vector<int>> g(sz);
		FOR(i, sz){
			tree[i].last = tree[i].first;
			g[tree[i].link].pb(i);
		}
		dfs(0, g);
		int ans = 0;
		FOR(i, sz){
			for(int j = tree[tree[i].link].len + 1; j <= tree[i].len; j++){
				if(tree[i].last - j + 1 > tree[i].first){
					ans++;
				} else {
					break;
				}
			}
		}
		return ans;
	}
} text;


char s[MN];
int main()
{
#ifdef MYLOCAL
    freopen("input.txt", "r", stdin);
 //   freopen("A9.out", "w", stdout);
#else
    freopen("prof.in", "r", stdin);
    freopen("prof.out", "w", stdout);
#endif
    gets(s);
    text.add_str(s);
    cout << text.take_last();
};
