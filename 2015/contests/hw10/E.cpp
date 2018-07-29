
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
#define MN 1000100
#define SM 26
//================================
struct automato
{
	struct leaf
	{
		lo link, len;
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
	void dfs(int id, vector<int> &val){
		val[id]= 0;
		for(auto pa : tree[id].nex){
			int to = pa.second;
			if(pa.first > 13){
				if(val[to] == -1)
					dfs(to, val);
				val[id] |= val[to];
			} else {
				val[id] |= (1<<(pa.first));
			}
		}
	}
	void dfs2(int id, int fin, char *res, int pos){
		res[pos] = '\0';
		if(fin == id){
			puts(res);
			return;
		}
		for(auto pa : tree[id].nex){
			int to = pa.second;
			if(pa.first > 13 && tree[to].len == tree[id].len + 1){
				res[pos] = pa.first;
				res[pos + 1] = '\0';
				dfs2(to, fin, res, pos + 1);
			}
		}
	}
	void counter(int num, char *s){
		vector<int> val(sz, -1);
		dfs(0, val);
		int best = 0, bestpos = 0;
		FOR(i, sz){
			if(val[i] == ((1<<num) - 1) * 2 && tree[i].len > best){
				best = tree[i].len;
				bestpos = i;
			}
		}
		dfs2(0, bestpos, s, 0);
	}
} text;


char s[MN], res[MN];
int main()
{
#ifdef MYLOCAL
    freopen("input.txt", "r", stdin);
 //   freopen("A9.out", "w", stdout);
#else
    freopen("substr3.in", "r", stdin);
    freopen("substr3.out", "w", stdout);
#endif
    int n;
    scanf("%d\n", &n);
    int now = 0;
    FOR(i, n ){
    	scanf("%s", s);
    	int len = strlen(s);
    	strcpy(res + now, s);
    	now += len;
    	res[now] = i + 1;
    	res[now + 1] = '\0';
    	now++;
    }
    text.add_str(res);
    text.counter(n, s);
};
