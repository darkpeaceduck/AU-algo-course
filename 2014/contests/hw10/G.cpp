
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
//#define all(a) (a).begin(), (a).end()
#define DEB(...) fprintf(stderr,__VA_ARGS__)
#define pi 3.14159265358979323
#define eps 1e-7
#define MN 100100
#define sz(n) (lo) (n).size()
#define SM 40
const li INF = 2e9;

using namespace std;

vector<lo> g[MN];
lo used[MN], fr[MN];
bool dfs(lo id)
{
	used[id] = 1;
	FOR(i, sz(g[id]))
	{
		lo to = g[id][i];
		if(used[to] == 1)
		{
			lo now = id;
			vector<lo> outp;
			while(1)
			{
				outp.pb(now);
				if(now == to)
					break;
				now = fr[now];
			}
			cout << "YES" << endl;
			reverse(outp.begin(), outp.end());
			FOR(i, sz(outp))
			{
				printf("%d ", outp[i] + 1);
			}
			return true;
		}
		if(!used[to])
		{
			fr[to] = id;
			if(dfs(to))
				return true;
		}
	}
	used[id] = 2;
	return false;
}
int main()
{
#ifdef MYLOCAL
     //freopen("perm.ou t", "w", stdout);
    freopen("input.txt", "r", stdin);
#else
    freopen("cycle.in", "r", stdin);
    freopen("cycle.out", "w",stdout);
#endif
    lo n, m;
    cin >> n >> m;
	FOR(i, m)
	{
		lo a, b;
		scanf("%d%d", &a, &b);
		a--;
		b--;
		g[a].pb(b);
	}
	FOR(i, n)
	{
		if(!used[i] && dfs(i))
		{
			return 0;
		}
	}
	cout << "NO";
}
