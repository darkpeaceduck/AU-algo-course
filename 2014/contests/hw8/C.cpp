
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
#define DEB(...) fprintf(stderr,__VA_ARGS__)
#define pi 3.14159265358979323
//#define eps 1e-3
#define MN 200000
#define sz(n) (lo) (n).size()
#define SM 40
const li INF = 2e9;


using namespace std;

lo dp[MN];
vector<lo> g[MN];
void dfs(lo id)
{
	FOR(i, sz(g[id]))
	{
		lo to = g[id][i];
		dfs(to);
		if(!dp[to])
			dp[id] = 1;
	}
}
int main(){
#ifdef MYLOCAL
	 //freopen("perm.out", "w", stdout);
	freopen("input.txt", "r", stdin);
#else
	freopen("chess.in", "r", stdin);
	freopen("chess.out", "w",stdout);
#endif
	lo n;
	cin >> n;
	lo root;
	FOR(i, n)
	{
		lo a;
		scanf("%d", &a);
		a--;
		if(a >= 0)
			g[a].pb(i);
		else
			root = i;
	}
	dfs(root);
	cout << (!dp[root] ? "NO" : "YES");
}
