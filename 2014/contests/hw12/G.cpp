
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
lo dest[MN];
lo p[MN];
void bfs(lo id)
{
	set<pair<lo, lo> > ok;
	dest[id] = 0;
	ok.insert(mp(dest[id], id));
	while(!ok.empty())
	{
		id = ok.begin()->second;
		ok.erase(ok.begin());
		FOR(i, sz(g[id]))
		{
			lo to = g[id][i].first;
			lo d = g[id][i].second;
			if(dest[to] > dest[id] + d)
			{
				set<pair<lo, lo> >::iterator it = ok.find(mp(dest[to], to));
				if(it != ok.end())
					ok.erase(it);
				dest[to] = dest[id] + d;
				p[to] = id;
				ok.insert(mp(dest[to], to));
			}
		}
	}
}

void re(lo a, lo start)
{
	if(a != start)
		re(p[a], start );
	printf("%d ", a + 1);
}
int main()
{
#ifdef MYLOCAL
     //freopen("perm.ou t", "w", stdout);
    freopen("input.txt", "r", stdin);
#else
    freopen("distance.in", "r", stdin);
    freopen("distance.out", "w",stdout);
#endif
    lo n, m;
    cin >> n >> m;
    lo A, B;
    cin >> A >> B;
    A--;
    B--;
    FOR(i, m)
    {
    	lo a, b, c;
    	scanf("%d%d%d", &a, &b, &c);
    	a--;
    	b--;
    	g[b].pb(mp(a, c));
    	g[a].pb(mp(b, c));
    }
    FOR(i, MN)
    	dest[i] = INF;
    bfs(A);
    if(dest[B] == INF)
    {
    	cout << -1;
    	return 0;
    }
    cout << dest[B] << endl;
//    re(B, A);
}


