
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
#define MN 100100
#define sz(n) (lo) (n).size()
#define SM 40
const li INF = 2e9;

using namespace std;

lo used[MN];
vector<lo> g[MN], gr[MN];
vector<lo> order;
void dfs(lo id)
{
	used[id]++;
	FOR(i, sz(g[id]))
	{
		lo to = g[id][i];
		if(!used[to])
			dfs(to);
	}
	order.pb(id);
}
void dfs2(lo id, lo color)
{
	used[id] = color;
	FOR(i, sz(gr[id]))
	{
		lo to = gr[id][i];
		if(!used[to])
			dfs2(to, color);
	}
}
int main()
{
#ifdef MYLOCAL
     //freopen("perm.ou t", "w", stdout);
    freopen("input.txt", "r", stdin);
#else
    freopen("condense2.in", "r", stdin);
    freopen("condense2.out", "w",stdout);
#endif
    lo n, m;
    cin >> n >> m;
    FOR(i, m)
	{
		lo a, b;
		scanf("%d%d", &a, &b);
		a--;
		b--;
			g[a].pb(b);
			gr[b].pb(a);
	}
	FOR(i, n){
		if(!used[i])
			dfs(i);
	}
	reverse(all(order));
	memset(used, 0, sizeof used);
	lo ptr = 0;
	FOR(i, n)
	{
		if(!used[order[i]])
		{
			dfs2(order[i], ++ptr);
		}
	}
	lo ans = 0;
	set<pair<lo, lo> > yep;
	FOR(i, n)
	{
		FOR(j, sz(g[i]))
		{
			lo to = g[i][j];
			if(used[i] != used[to])
			{
				yep.insert(mp(used[i], used[to]));
			}
		}
	}
	cout << sz(yep);
}
