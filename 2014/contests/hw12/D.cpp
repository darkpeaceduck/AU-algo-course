
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
#define MN 200000
#define sz(n) (lo) (n).size()
#define SM 40
const li INF = 2e9;

using namespace std;

//#include <memory>
//#include <pthread.h>
vector<pair<lo, lo>  > g[MN];
lo used[MN];
lo dest[MN];
lo is[MN];
lo p[MN];
void bfs(lo id)
{
	queue<lo> q[2];
	lo cur_q = 0;
	q[cur_q].push(id);
	used[id]++;
	FOR(i, MN)
		dest[i] = INF;
	dest[id] = 0;
	while(!q[0].empty() || !q[1].empty())
	{
		while(!q[cur_q].empty())
		{
			id = q[cur_q].front();
			q[cur_q].pop();
			FOR(i, sz(g[id]))
			{
				lo to = g[id][i].first;
				lo add =g[id][i].second;
				if(!used[to])
				{
					used[to]++;
					dest[to] = dest[id] + add;
					p[to] = id;
					q[(cur_q + add)%2].push(to);
				}
			}
		}
		cur_q = (cur_q + 1) % 2;
	}
}

void re(lo a, lo h)
{
	if(a)
		re(p[a], h + 1);
	else
		printf("%d\n", h);
	printf("%d ", a + 1);
}
int main()
{
#ifdef MYLOCAL
     //freopen("perm.ou t", "w", stdout);
    freopen("input.txt", "r", stdin);
#else
    freopen("island.in", "r", stdin);
    freopen("island.out", "w",stdout);
#endif
    lo n, m;
    cin >> n >> m;
    FOR(i, n)
    	scanf("%d", &is[i]);
    FOR(i, m)
    {
    	lo a, b;
    	scanf("%d%d", &a, &b);
    	a--;
    	b--;
    	lo add = is[a] != is[b];
    	g[b].pb(mp(a, add));
    	g[a].pb(mp(b, add));
    }
    bfs(0);
    if(!used[n-1])
    {
    	cout << "impossible";
    	return 0;
    }
    cout << dest[n-1] << " ";
    re(n-1, 1);
}


