
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

lo dp[MN][2], a[MN];
vector<lo> g[MN];
void dfs(lo id, lo p)
{
	dp[id][1] = a[id];
	FOR(i, sz(g[id])){
		lo to = g[id][i];
		if(to == p)
			continue;
		dfs(to, id);
		dp[id][1] += dp[to][0];
		dp[id][0] += max(dp[to][0], dp[to][1]);
	}
}

int main()
{
#ifdef MYLOCAL
     //freopen("perm.ou t", "w", stdout);
    freopen("input.txt", "r", stdin);
#else
    freopen("selectw.in", "r", stdin);
    freopen("selectw.out", "w",stdout);
#endif
    lo n;
    cin >> n;
    lo root = 0;
    FOR(i, n)
    {
    	lo b;
    	scanf("%d%d", &b, &a[i]);
    	b--;
    	if(b < 0)
    	{
    		root = i;
    	}
    	else
    	{
    		g[b].pb(i);
    	}
    }
    dfs(root, -1);
    cout << max(dp[root][0], dp[root][1]);
}
