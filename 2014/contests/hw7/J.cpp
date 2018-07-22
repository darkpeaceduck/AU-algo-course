
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
#define DEB(...) fprintf(err,__VA_ARGS__)
#define pi 3.14159265358979323
#define eps 1e-3
#define MN 100100
#define sz(n) (lo) (n).size()
#define SM 1000100
const li INF = 1e9;


using namespace std;

vector<lo> g[MN];
lo a[MN];
lo used[MN];
void dfs(lo id)
{
	used[id]++;
	FOR(i, sz(g[id]))
	{
		lo to = g[id][i];
		if(!used[to])
		dfs(to);
		a[id] = max(a[id], a[to] + 1);
	}
}
int main(){
#ifdef MYLOCAL
	freopen("input.txt", "r", stdin);
	 //freopen("perm.out", "w", stdout);
#else
	freopen("longpath.in", "r", stdin);
	freopen("longpath.out", "w",stdout);
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
	lo ans = 0;
	FOR(i, n)
	{
		if(!used[i])
			dfs(i);
		ans = max(ans, a[i]);
	}
	cout << ans;
}
