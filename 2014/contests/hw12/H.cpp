
//#pragma comment(linker, "/STACK:100000000000000")
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
#define lo long long int
#define li long long int
#define db double
#define pb push_back
#define FOR(i, n) for(lo (i) = 0; (i) < (n); (i)++)
#define all(a) (a).begin(), (a).end()
#define DEB(...) fprintf(stderr,__VA_ARGS__)
#define pi 3.14159265358979323
#define eps 1e-7
#define MN 200000
#define sz(n) (lo) (n).size()
#define SM 40
const li INF = 2e18;

using namespace std;

//#include <memory>
//#include <pthread.h>
li dest[MN], cheat[MN];
lo p[MN];
vector<lo> g[MN];
void dfs(lo id)
{
	cheat[id]++;
	FOR(i, sz(g[id]))
	{
		lo to = g[id][i];
		if(!cheat[to])
			dfs(to);
	}
}
int main()
{
#ifdef MYLOCAL
     //freopen("perm.ou t", "w", stdout);
    freopen("input.txt", "r", stdin);
#else
    freopen("path.in", "r", stdin);
    freopen("path.out", "w",stdout);
#endif
    lo n, m;
    cin >> n >> m;
    lo A;
    cin >> A;
    A--;
    vector<pair<pair<lo, lo>, li> > edge;
    FOR(i, m)
    {
    	lo a, b;
    	li c;
    	cin >> a >> b >> c;
    	a--;
    	b--;
    	edge.pb(mp(mp(a, b), c));
    	g[a].pb(b);
    }
    FOR(i, n)
    	dest[i] = INF;
    dest[A] = 0;
    memset(p, -1, sizeof p);
    FOR(i, n)
    {
    	FOR(j, sz(edge))
		{
    		lo a = edge[j].first.first;
    		lo b = edge[j].first.second;
    		li c = edge[j].second;
    		if(dest[a] == INF)
    			continue;
    		if(dest[b] > dest[a] + c)
    		{
    			if(i == n - 1)
    				cheat[b]++;
    			dest[b] = dest[a] + c;
    			p[b] = a;
    		}
		}
    }
    vector<lo> ok;
    FOR(i, n)
    {
    	if(cheat[i])
    	{
    		ok.pb(i);
    		cheat[i] = 0;
    	}
    }
    FOR(k, sz(ok))
    {
    	lo i = ok[k];
    		lo y = i;
    		for(lo j = 0 ; j < n; j++)
    			y = p[y];
    		if(y != -1)
    			dfs(y);
    		dfs(i);
    }
    FOR(i, n)
    {
    	if(dest[i] == INF)
    		printf("*\n");
    	else if(cheat[i])
    		printf("-\n");
    	else
    		cout << dest[i] << endl;
    }
}


