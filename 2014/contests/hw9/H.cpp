
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
#define MN 1<<15
#define sz(n) (lo) (n).size()
#define SM 17
const li INF = 2e9;

using namespace std;

lo sum[MN];
lo dp[MN][SM];
lo fr[MN][SM];
lo ans[MN];
lo n;
void re(lo a, lo k)
{
	if(k == 1)
	{
		FOR(i, n)
		{
			if(a & (1<<i))
			{
				ans[i] = k;
			}
		}
		return;
	}
	lo mask = fr[a][k];
	re(mask, k - 1);
	FOR(i, n)
	{
		if((a ^ mask) & (1<<i))
		{
			ans[i] = k;
		}
	}
}
int main()
{
#ifdef MYLOCAL
	 //freopen("perm.ou t", "w", stdout);
	freopen("input.txt", "r", stdin);
#else
	freopen("fair.in", "r", stdin);
	freopen("fair.out", "w",stdout);
#endif
	lo k;
	cin >> n >> k;
	FOR(i, n)
	{
		cin >> sum[1<<i];
	}
	FOR(i, (1<<n))
	{
		FOR(j, n)
		{
			dp[i][j] = dp[i][j + 1] = INF;
			if(!(i & (1<<j)))
			{
				sum[i | (1<<j)] = sum[i] + sum[1<<j];
			}
		}
	}
	lo C = (sum[(1<<n) - 1]) / k;
	lo to = min(n, k);
	FOR(i, (1<<n))
	{
		dp[i][1] = (sum[i] - C) * (sum[i] - C);
		for(lo j = 2; j <= to; j++)
		{
			for(lo d = i; d > 0; d = (d - 1) & i)
			{
				lo mask = (i ^ d);
				lo o;
				if(dp[mask][j - 1] != INF &&
						dp[i][j] > (o = dp[mask][j - 1] + (sum[d] - C) * (sum[d] - C)))
				{
					dp[i][j] = o;
					fr[i][j] = mask;
				}
			}
		}
	}
	db res = dp[(1<<n) - 1][min(n, k)] + max(0, k - n) * C * C;
	res /= k;

	cout << fixed << setprecision(6) << sqrt(res) << endl;
	re((1<<n) - 1, min(n, k));
	FOR(i, n)
		cout << ans[i] << " ";
}


