
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
#define MN 1000
#define sz(n) (lo) (n).size()
#define SM 1000100
const li INF = 1e9;


using namespace std;

lo dp[MN][MN];
lo ma[MN][MN];
int main(){
#ifdef MYLOCAL
	freopen("input.txt", "r", stdin);
	 //freopen("perm.out", "w", stdout);
#else
	freopen("field.in", "r", stdin);
	freopen("field.out", "w",stdout);
#endif
	lo n, m;
	cin >> n >> m;
	swap(n, m);
	FOR(i, n) FOR(j, m)
	{
		scanf("%d", &ma[i][j]);
	}
	FOR(i, n) FOR(j, m)
			dp[i][j] = INF;
	dp[0][0] = 0;
	const pair<lo, lo> step[2] = {mp(0, 1), mp(1, 0)};
	FOR(i, n) FOR(j, m)
	{
		FOR(k, 2)
		{
			lo x = i + step[k].first;
			lo y = j + step[k].second;
			dp[x][y] = min(dp[x][y], dp[i][j] + abs(ma[i][j] - ma[x][y]));
		}
	}
	cout << dp[n - 1][m - 1];
}
