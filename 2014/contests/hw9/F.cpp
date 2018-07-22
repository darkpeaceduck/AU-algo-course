
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
#define eps 1e-3
#define MN 1<<10
#define sz(n) (lo) (n).size()
#define SM 19
const li INF = 2e9;

using namespace std;

lo dp[MN], val[MN];
int main(){
#ifdef MYLOCAL
	 //freopen("perm.ou t", "w", stdout);
	freopen("input.txt", "r", stdin);
#else
	freopen("cube.in", "r", stdin);
	freopen("cube.out", "w",stdout);
#endif
	lo n;
	cin >> n;
	FOR(i, (1<<n))
	{
		cin >> val[i];
	}
	dp[0] = val[0];
	FOR(i, (1<<n))
	{
		FOR(j, n)
		{
			if(!(i & (1<<j)))
			{
				dp[i | (1<<j)] = max(dp[i | (1<<j)], dp[i] + val[i | (1<< j)]);
			}
		}
	}
	cout << dp[(1<<n) - 1];
}


