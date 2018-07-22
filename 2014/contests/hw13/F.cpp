
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

//#include <memory>
//#include <pthread.h>
lo d[MN], color[MN], nex[MN];
vector<pair<lo, lo> > g[MN];
int main()
{
#ifdef MYLOCAL
     //freopen("perm.ou t", "w", stdout);
    freopen("input.txt", "r", stdin);
#else
    freopen("negcycle.in", "r", stdin);
    freopen("negcycle.out", "w",stdout);
#endif
    lo n, m;
    cin >> n >> m;
    FOR(i, m)
    {
    	lo a, b, c;
    	scanf("%d%d%d", &a, &b, &c);
    	a--;
    	b--;
    	g[a].pb(mp(b, c));
    }
    FOR(i, MN)
    	d[i] = INF,
    	color[i] = -1;
    d[0] = 0;
    queue<lo> q;
    q.push(0);
    FOR(i, n)
    {
    	lo num = (int) q.size();
    	if(!num)
    		break;
    	FOR(j, num)
    	{
    		lo id = q.front();
    		q.pop();
    		FOR(k, sz(g[id]))
    		{
    			lo to = g[id][k].first;
    			lo len = g[id][k].second;
    			if(d[to] > d[id] + len)
    			{
    				if(color[to] != i)
    				{
    					q.push(to);
    					color[to] = i;
    				}
    				d[to] = d[id] + len;
    			}
    		}
    	}
    }
    printf(q.empty() ? "no" : "yes");
}
