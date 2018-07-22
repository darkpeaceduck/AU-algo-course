
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
#define MN 1010
#define sz(n) (lo) (n).size()
#define SM 40
const li INF = 2e9;

using namespace std;

//#include <memory>
//#include <pthread.h>
vector<lo > g[MN];
lo used[MN];
lo dest[MN];
void bfs(lo id)
{
	queue<lo> q;
	q.push(id);
	used[id]++;
	FOR(i, MN)
		dest[i] = INF;
	dest[id] = 0;
	while(!q.empty())
	{
		id = q.front();
		q.pop();
		FOR(i, sz(g[id]))
		{
			lo to = g[id][i];
			if(!used[to])
			{
				used[to]++;
				dest[to] = dest[id] + 1;
				q.push(to);
			}
		}
	}
}
int main()
{
#ifdef MYLOCAL
     //freopen("perm.ou t", "w", stdout);
    freopen("input.txt", "r", stdin);
#else
    freopen("sumdist.in", "r", stdin);
    freopen("sumdist.out", "w",stdout);
#endif
    lo n, m;
    cin >> n >> m;
    FOR(i, m)
    {
    	lo a, b;
    	scanf("%d%d", &a, &b);
    	a--;
    	b--;
    	g[b].pb(a);
    	g[a].pb(b);
    }
    li outp = 0;
    FOR(i, n)
    {
    	memset(used, 0, sizeof used);
    	bfs(i);
    	FOR(j, n)
    	{
    		outp += dest[j];
    	}
    }
    cout << outp / 2;
}


