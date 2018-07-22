
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
#define MN 1<<19
#define sz(n) (lo) (n).size()
#define SM 19
const li INF = 2e9;

using namespace std;

lo dp[MN][SM];
lo fr[MN][SM];
lo go[SM][SM];
lo n,m ;
void re(lo a, lo en)
{
	if(!a)
		return;
	re(a ^ (1<<en), fr[a][en]);
	cout << en + 1 << " ";
}
int main(){
#ifdef MYLOCAL
	 //freopen("perm.ou t", "w", stdout);
	freopen("input.txt", "r", stdin);
#else
	freopen("salesman.in", "r", stdin);
	freopen("salesman.out", "w",stdout);
#endif

	cin >> n;
	FOR(i, n) FOR(j, n)
	{
		cin >> go[i][j];
	}
	FOR(i, (1<<n))
	{
		FOR(k, n)
				dp[i][k] = INF;
	}
	FOR(i, n)
		dp[1<<i][i] = 0;
	FOR(i, (1<<n))
	{
		FOR(j, n)
		{
			if(dp[i][j] == INF)
				continue;
			if(i & (1<<j))
			{
				FOR(k, n)
				{
					if(i & (1<<k))
						continue;
					lo num = dp[i][j] + go[j][k];
					lo mask = i | (1<<k);
					if(dp[mask][k] > num)
					{
						dp[mask][k] = num;
						fr[mask][k] = j;
					}
				}
			}
		}
	}
	lo last = 0;
	FOR(i, n)
	{
		if(dp[(1<<n) - 1][i] < dp[(1<<n) - 1][last])
			last = i;
	}
	cout << dp[(1<<n) - 1][last] << endl;
	re((1<<n) - 1, last);
}


