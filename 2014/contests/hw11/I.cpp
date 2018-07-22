
#pragma comment(linker, "/STACK:100000000000000")
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

//#include <memory>
//#include <pthread.h>

vector<lo> g[MN];
vector<pair<lo, lo> > q[MN];
li dn[MN], ans[MN], used[MN];
void count_dn(lo id, lo p)
{
	used[id]++;
	dn[id] = 1;
	FOR(i, sz(g[id])){
		lo to = g[id][i];
		if(to == p)
			continue;
		count_dn(to, id);
		dn[id] += dn[to];
	}
}
void dfs(lo id, lo p, li up)
{
	FOR(i, sz(q[id])){
		lo to = q[id][i].first;
		lo edge_id = q[id][i].second;
		if(to == p)
			ans[edge_id] = up * dn[id];
	}
	FOR(i, sz(g[id])){
		lo to = g[id][i];
		if(to == p)
			continue;
		dfs(to, id, up + dn[id] - dn[to]);
	}
}

int main()
{
#ifdef MYLOCAL
     //freopen("perm.ou t", "w", stdout);
    freopen("input.txt", "r", stdin);
#else
    freopen("health.in", "r", stdin);
    freopen("health.out", "w",stdout);
#endif
    lo n, m;
    cin >> n >> m;
    vector<pair<lo, lo> > edge(m);
    FOR(i, m)
    {
    	lo a, b;
    	scanf("%d%d", &a, &b);
    	a--;
    	b--;
    	g[a].pb(b);
    	g[b].pb(a);
    	edge[i] = mp(a, b);
    }
    lo Q;
    cin >> Q;
    FOR(i, Q)
    {
    	lo id;
    	scanf("%d", &id);
    	id--;
    	lo a = edge[id].first;
    	lo b = edge[id].second;
    	q[a].pb(mp(b, i));
    	q[b].pb(mp(a, i));
    }
    FOR(i, n)
    {
    	if(!used[i])
    	{
    		count_dn(i, -1);
    		dfs(i, -1, 0);
    	}
    }
    FOR(i, Q)
    {
    	printf("%I64d\n", ans[i]);
    }
}
