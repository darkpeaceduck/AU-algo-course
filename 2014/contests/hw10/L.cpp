
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
lo used[MN], in[MN], p[MN];
char color[MN];
vector<lo> order;
set<pair<lo, lo> > edge;
bool dfs(lo id)
{
	used[id]++;
	FOR(i, sz(g[id]))
	{
		lo to = g[id][i];
		if(!used[to])
		{
			p[to] = id;
			if(!dfs(to))
				return false;
		}
	}
	order.pb(id);
	return true;
}
int main()
{
#ifdef MYLOCAL
     //freopen("perm.ou t", "w", stdout);
    freopen("input.txt", "r", stdin);
#else
    freopen("unitopsort.in", "r", stdin);
    freopen("unitopsort.out", "w",stdout);
#endif
    lo n, m;
    cin >> n >> m;
    /*FOR(i, n)
    {
    	cin >> color[i];
    }
    */
    FOR(i, m)
    {
    	lo a, b;
    	scanf("%d%d", &a, &b);
    	a--;
    	b--;
    	g[a].pb(b);
    	in[b]++;
    }
    lo fcnt = 0, scnt = 0, fr;
    FOR(i, n)
    {
    	if(in[i] == 0)
    		fcnt++, fr = i;
    	if(sz(g[i]) == 0)
    		scnt++;
    }
    if(fcnt == 1 && scnt == 1)
    {
    	dfs(fr);
    	if(sz(order) == n)
    	{
    		reverse(all(order));
    		FOR(i, n - 1)
			{
    			bool yep = false;
    			FOR(j, sz(g[order[i]]))
    			{
    				if(g[order[i]][j] == order[i + 1])
    				{
    					yep = true;
    				}
    			}
    			if(!yep)
    			{
    				cout << "NO";
    				return 0;
    			}
			}
    		cout << "YES" << endl;
    		FOR(i, n)
    			printf("%d ", order[i] + 1);
    		return 0;
    	}
    }
    cout << "NO";
}
