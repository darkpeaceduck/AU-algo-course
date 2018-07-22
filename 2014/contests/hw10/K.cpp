
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
#include <functional>
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
#define eps 1e-7
#define MN 300100
#define sz(n) (lo) (n).size()
#define SM 40
const li INF = 2e9;

using namespace std;

vector<lo> g[MN];
vector<pair<lo, lo> > gr[MN];
lo used[MN], tin[MN], fup[MN], timer = 1, iscut[MN];
void dfs(lo id, lo p, vector<lo> &outp)
{
	used[id]++;
	tin[id] = fup[id] = timer++;
	lo children = 0;
	FOR(i, sz(g[id]))
	{
		lo to = g[id][i];
		if(to == p)
			continue;
		if(used[to])
		{
			fup[id] = min(fup[id], tin[to]);
		}
		else
		{
			children++;
			dfs(to, id, outp);
			fup[id] = min(fup[id], fup[to]);
			if(tin[id] <= fup[to] && p != -1)
			{
				outp.pb(id);
			}
		}
	}
	if(p == -1 && children > 1)
		outp.pb(id);
}

lo ptr = 0;
lo ans[MN];
void coloring(lo id, lo color, lo p)
{
	used[id]++;
	FOR(i, sz(gr[id]))
	{
		if(id == p)
			continue;
		lo to = gr[id][i].first;
		if(!used[to])
		{
			if(tin[id] <= fup[to])
			{
				++ptr;
				ans[gr[id][i].second] = ptr;
				coloring(to, ptr, id);
			}
			else
			{
				ans[gr[id][i].second] = color;
				coloring(to, color, id);
			}
		}
		else
			if(tin[id] >= tin[to])
				ans[gr[id][i].second] = color;
	}
}

int main()
{
#ifdef MYLOCAL
     //freopen("perm.ou t", "w", stdout);
    freopen("input.txt", "r", stdin);
#else
    freopen("biconv.in", "r", stdin);
    freopen("biconv.out", "w",stdout);
#endif
    lo n, m;
    cin >> n >> m;
    vector<pair<lo, lo> > edge;
	FOR(i, m)
	{
		lo a, b;
		scanf("%d%d", &a, &b);
		if(a == b)
			continue;
		a--;
		b--;
		g[a].pb(b);
		g[b].pb(a);
		gr[a].pb(mp(b, i));
		gr[b].pb(mp(a, i));
		edge.pb(mp(a, b));
	}
	vector<lo> outp;
	FOR(i, n)
	{
		if(!used[i])
			dfs(i, -1, outp);
	}
	memset(used, 0, sizeof used);
	FOR(i, n)
		if(!used[i])
			coloring(i, -1, -1);
	cout << ptr << endl;
	FOR(i, m)
		printf("%d ", ans[i]);
}
