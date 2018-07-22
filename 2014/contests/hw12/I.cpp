
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
#include <fstream>
#include <cassert>
#include <complex>

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
#define db long double
#define pb push_back
#define FOR(i, n) for(lo (i) = 0; (i) < (n); (i)++)
#define all(a) (a).begin(), (a).end()
#define DEB(...) fprintf(stderr,__VA_ARGS__)
#define pi 3.14159265358979323
#define eps 1e-7
#define MN 200000
#define sz(n) (lo) (n).size()
#define SM 12
const lo INF = 2e9;

using namespace std;

#include <memory>
//#include <pthread.h>


vector<pair<lo,lo> > g[MN];
lo dist[MN], color[MN];
int main()
{
#ifdef MYLOCAL
//     freopen("perm.ou t", "w", stdout);
	freopen("input.txt", "r", stdin);
#else
    freopen("shortest.in", "r", stdin);
    freopen("shortest.out", "w",stdout);
#endif
	lo n, m;
	cin >> n >> m;
	FOR(i ,m)
	{
		lo a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		a--;
		b--;
		g[a].pb(mp(b, c));
	}
	lo K;
	cin >> K;
	FOR(i, K)
	{
//		cout << "-------" << endl;
		const lo qsz = 3;
		const int p = 1000;
		lo a, b;
		scanf("%d%d", &a, &b);
		a--;
		b--;
		queue<lo> q[qsz];
		lo now = 0;

		q[0].push(a);
		dist[a] = 0;
		color[a] = i + 1;

		bool taked = false;
		while(1)
		{
			bool ex = false;
			if(taked)
				break;
			FOR(i, 3)
				ex |= !q[i].empty();
			if(!ex)
				break;
			for(;;now = (now + 1) % 3)
			{
				if(!q[now].empty())
					break;
			}
			while(!q[now].empty())
			{
				lo id = q[now].front();
				if(id == b)
					taked = true;
				q[now].pop();
				FOR(j, sz(g[id]))
				{
					lo to = g[id][j].first;
					lo d = g[id][j].second;
					if(color[to] != i + 1)
					{
						color[to] = i + 1;
						dist[to] = INF;
					}
					if(dist[to] > dist[id] + d)
					{
						dist[to] = dist[id] + d;
						lo toq = (dist[to] / p) % 3;
//						cout << to << " " <<toq<<" "<<dist[to] << endl;
						q[toq].push(to);
					}
				}
			}
		}
		if(taked)
		{
			printf("%d\n", dist[b]);
		}
		else
			printf("-1\n");
	}
}

