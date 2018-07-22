
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
#define MN 1010
#define sz(n) (lo) (n).size()
#define SM 40
const li INF = 2e9;

using namespace std;

#include <memory>

lo a[MN][MN];
vector<lo> g[MN], gr[MN];
lo used[MN];
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
    freopen("avia.in", "r", stdin);
    freopen("avia.out", "w",stdout);
#endif
    lo n;
    cin >> n;
    lo maxi = 0;
    vector<pair<lo, pair<lo, lo> > > edge;
    FOR(i, n) FOR(j, n)
    {
    	scanf("%d", &a[i][j]);
    	maxi = max(maxi, a[i][j]);
    	edge.pb(mp(a[i][j], mp(i, j)));
    }
    sort(edge.begin(), edge.end());
    lo l = 0, r = maxi;
    while(l != r)
    {
    	lo m = (l + r ) / 2;
    	FOR(i, n)
    	{
    		g[i].clear();
    		vector<lo>().swap(g[i]);
    		gr[i].clear();
    		vector<lo>().swap(gr[i]);
    	}
    	FOR(i, sz(edge))
    	{
    		if(edge[i].first > m)
    			continue;
    		g[edge[i].second.first].pb(edge[i].second.second);
    		gr[edge[i].second.second].pb(edge[i].second.first);
    	}
    	order.clear();
    	memset(used, 0, sizeof used);
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
    	if(ptr == 1)
    		r = m;
    	else
    		l = m + 1;
    }
    cout << l;
}
