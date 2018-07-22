
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
//#define all(a) (a).begin(), (a).end()
#define DEB(...) fprintf(stderr,__VA_ARGS__)
#define pi 3.14159265358979323
#define eps 1e-7
#define MN 100100
#define sz(n) (lo) (n).size()
#define SM 40
const li INF = 2e9;

using namespace std;

vector<pair<lo, lo> > g[MN];
vector<lo> bridges[MN];
lo used[MN], tin[MN], fup[MN], timer = 1;
void dfs(lo id, lo p)
{
	used[id]++;
	tin[id] = fup[id] = timer++;
	FOR(i, sz(g[id]))
	{
		lo to = g[id][i].first;
		lo edge_id = g[id][i].second;
		if(edge_id == p)
			continue;
		if(used[to])
		{
			fup[id] = min(fup[id], tin[to]);
		}
		else
		{
			dfs(to, edge_id);
			fup[id] = min(fup[id], fup[to]);
			if(tin[id] < fup[to])
			{
				bridges[id].pb(to);
				bridges[to].pb(id);
			}
		}
	}
}

void delete_edges(lo id)
{
	sort(bridges[id].begin(), bridges[id].end());
	vector<pair<lo, lo> > newo;
	for(lo i = sz(g[id]) - 1; i >= 0; i--)
	{
		if(!bridges[id].empty() && bridges[id].back() == g[id][i].first)
		{
			bridges[id].pop_back();
			continue;
		}
		newo.pb(g[id][i]);
	}
	g[id] = newo;
}

void dfs2(lo id, vector<lo> &vis)
{
	used[id]++;
	vis.pb(id);
	FOR(i, sz(g[id]))
	{
		lo to = g[id][i].first;
		if(!used[to])
			dfs2(to, vis);
	}
}
int main()
{
#ifdef MYLOCAL
     //freopen("perm.ou t", "w", stdout);
    freopen("input.txt", "r", stdin);
#else
    freopen("bridges.in", "r", stdin);
    freopen("bridges.out", "w",stdout);
#endif
    lo n, m;
    cin >> n >> m;
	FOR(i, m)
	{
		lo a, b;
		scanf("%d%d", &a, &b);
		if(a == b)
			continue;
		a--;
		b--;
		g[a].pb(mp(b, i));
		g[b].pb(mp(a, i));
	}
	FOR(i, n)
	{
		sort(g[i].begin(), g[i].end());
	}
	FOR(i, n)
	{
		if(!used[i])
			dfs(i, -1);
	}
	FOR(i, n)
		delete_edges(i);
	memset(used, 0, sizeof used);
	vector<vector<lo> > ans;
	FOR(i, n)
	{
		if(!used[i])
		{
			vector<lo> vis;
			dfs2(i, vis);
			sort(vis.begin(), vis.end());
			ans.pb(vis);
		}
	}
	sort(ans.begin(), ans.end());
	cout<< sz(ans) << endl;
	FOR(i, sz(ans))
	{
		FOR(j, sz(ans[i]))
		{
			printf("%d ", ans[i][j] + 1);
		}
		printf("\n");
	}
}
