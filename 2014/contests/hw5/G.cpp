
///#pragma comment(linker, "/STACK:100000000000000")
#include <stdio.h>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <stack>
#include <queue>
#include <bitset>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string.h>
#include <cctype>

#include <cassert>


#include <ctime>
//#include <unordered_set>
//expr
/*#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
*/
//

#define mp make_pair
#define pb push_back
#define lo int
#define li long long int
#define db double
#define pb push_back
#define FOR(i, n) for(lo (i) = 0; (i) < (n); (i)++)
#define all(a) (a).begin(), (a).end()
#define DEB(...) fprintf(stderr,__VA_ARGS__)
#define pi 3.14159265358979323
#define eps 1e-4
#define MN 1000100
#define sz(n) (lo) (n).size()
#define SM 1000100
const li INF = 1e15;


using namespace std;


void inc(lo id, lo *fen, lo val)
{
	for(; id < MN; id += (id + 1) & -(id + 1))
	{
		fen[id]+= val;
	}
}
lo geti(lo id, lo *fen)
{
	lo res=0;
	for(; id >= 0; id -= (id + 1) & -(id + 1))
	{
		res += fen[id];
	}
	return res;
}
lo rev(lo a)
{
	return MN - 1 - a;
}
void shiftL(lo &ll, lo l, li &res, vector<lo> &g, lo *mini, lo *maxi)
{
	while(ll < l)
	{
		res -= geti(g[ll] - 1, mini);
		inc(g[ll], mini, -1);
		inc(rev(g[ll]), maxi, -1);
		ll++;
	}
}
void ReshiftL(lo &ll, lo l, li &res, vector<lo> &g, lo *mini, lo *maxi)
{
	while(ll > l)
	{
		ll--;
		inc(g[ll], mini, 1);
		inc(rev(g[ll]), maxi, 1);
		res += geti(g[ll] - 1, mini);
	}
}
void shiftR(lo &lr, lo r, li &res, vector<lo> &g, lo *mini, lo *maxi)
{
	while(lr < r)
	{
		lr++;
		inc(g[lr], mini, 1);
		inc(rev(g[lr]) , maxi, 1);
		res += geti(rev(g[lr]) - 1, maxi);
	}
}
void ReshiftR(lo &lr, lo r, li &res, vector<lo> &g, lo *mini, lo *maxi)
{
	while(lr > r)
	{
		res -= geti(rev(g[lr]) - 1, maxi);
		inc(g[lr], mini, -1);
		inc(rev(g[lr]) , maxi, -1);
		lr--;
	}
}
void sol1(vector<lo> &g, vector<pair<lo, lo> > &s)
{
	lo *maxi = new lo[MN], *mini = new lo[MN];
	memset(maxi, 0, sizeof maxi);
	memset(mini, 0, sizeof mini);
	lo ll = 0, lr = -1;
	li res = 0;
	FOR(i, sz(s))
	{
		lo l = s[i].first, r =s[i].second;
		l--;
		r--;
		shiftL(ll, l, res, g, mini, maxi);
		shiftR(lr, r, res, g, mini, maxi);
		printf("%I64d\n", res);
	}
}
void sol2(vector<lo> &g, vector<pair<lo, lo> > &s)
{
	lo *maxi = new lo[MN], *mini = new lo[MN];
	memset(maxi, 0, sizeof maxi);
	memset(mini, 0, sizeof mini);
	lo ll = 0, lr = -1;
	li res = 0;
	lo SQRT = 600;
	vector<li> ans(sz(s));
	vector<vector<pair<pair<lo,lo>, lo> > > in(sz(g) / SQRT + 10);
	FOR(i, sz(s))
	{
		in[(s[i].first-1) / SQRT].pb(mp(mp(s[i].second, s[i].first), i));
	}
	FOR(i, sz(in))
	{
		sort(in[i].begin(), in[i].end());
		FOR(j, sz(in[i]))
		{
			lo l = in[i][j].first.second;
			lo r = in[i][j].first.first;
			lo id = in[i][j].second;
			l--;
			r--;
			shiftL(ll, l, res, g, mini, maxi);
			shiftR(lr, r, res, g, mini, maxi);
			ReshiftL(ll, l, res, g, mini, maxi);
			ReshiftR(lr, r, res, g, mini, maxi);
			ans[id] = res;
		}
	}
	FOR(i, sz(s))
	{
		printf("%I64d\n", ans[i]);
	}
}
int main(){
#ifdef MYLOCAL
	freopen("input.txt", "r", stdin);
	 //freopen("perm.out", "w", stdout);
#else
	freopen("invseg.in", "r", stdin);
	freopen("invseg.out", "w",stdout);
#endif
	lo n;
	cin >> n;
	vector<lo> g(n);
	FOR(i, n)
	{
		scanf("%d", &g[i]);
	}
	lo m;
	cin >> m;
	vector<pair<lo,lo> > s(m);
	FOR(i, m)
	{
		lo l, r;
		scanf("%d%d", &l, &r);
		s[i] = mp(l, r);
	}
	sol2(g, s);
}
