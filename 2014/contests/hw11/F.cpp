
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

//#include <memory>
//#include <pthread.h>

lo between[MN][MN];
lo is[MN][MN];
vector<lo> g[MN];

void delete_edge(lo a, lo b){
	if(a == b)
		return;
	between[a][b]--;
	between[b][a]--;
	if(!between[b][a])
	{
		is[a][g[a].back()] = is[a][b];
		swap(g[a][sz(g[a]) - 1], g[a][is[a][b]]);
		g[a].pop_back();
		is[b][g[b].back()] = is[b][a];
		swap(g[b][sz(g[b]) - 1], g[b][is[b][a]]);
		g[b].pop_back();
	}
}

void add_edge(lo a, lo b)
{
	if(a == b)
		return;
	between[a][b]++;
	between[b][a]++;
	if(between[b][a] == 1)
	{
		is[a][b] = sz(g[a]); g[a].pb(b);
		is[b][a] = sz(g[b]); g[b].pb(a);
	}
}

lo used[MN];
lo dfs(lo id)
{
	used[id]++;
	lo res = 1;
	FOR(i, sz(g[id])){
		lo to = g[id][i];
		if(!used[to])
			res += dfs(to);
	}
	return res;
}
int main()
{
#ifdef MYLOCAL
     //freopen("perm.ou t", "w", stdout);
    freopen("input.txt", "r", stdin);
#else
    freopen("roadwork.in", "r", stdin);
    freopen("roadwork.out", "w",stdout);
#endif
    lo n, m;
    cin >> n >> m;
    lo edges = 0;
    scanf("\n");
    FOR(i, m)
    {
    	char type;
    	lo u, v;
    	scanf("%c%d%d\n", &type, &u, &v);
    	u--;
    	v--;
    	if(type == 'F')
    	{
    		edges++;
    		add_edge(u, v);
    	}
    	else
    	{
    		edges--;
    		delete_edge(u, v);
    	}
    	if(edges == n - 1)
    		memset(used, 0, sizeof used);
    	printf(edges == n - 1 && dfs(0) == n? "YES\n" : "NO\n");
    }
}
