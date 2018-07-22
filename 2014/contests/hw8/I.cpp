
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
#define lo long long int
#define li long long int
#define db double
#define pb push_back
#define FOR(i, n) for(lo (i) = 0; (i) < (n); (i)++)
//#define all(a) (a).begin(), (a).end()
#define DEB(...) fprintf(stderr,__VA_ARGS__)
#define pi 3.14159265358979323
//#define eps 1e-3
#define MN 1000100
#define sz(n) (lo) (n).size()
#define SM 40
const li INF = 2e12;


using namespace std;

li dp[MN], is[MN], fr[MN], a[MN];
void re(lo a)
{
	if(a == -1)
		return;
	re(fr[a]);
	printf("%I64d\n", a + 1);
}
int main(){
#ifdef MYLOCAL
	 //freopen("perm.ou	t", "w", stdout);
	freopen("input.txt", "r", stdin);
#else
	freopen("subseq.in", "r", stdin);
	freopen("subseq.out", "w",stdout);
#endif
	FOR(i, MN)
	{
		dp[i] = -INF;
		fr[i] = -1;
		is[i] = -1;
	}
	dp[0] = INF;
	lo n;
	cin >> n;
	FOR(i, n)
	{
//		cin >> a[i];
		scanf("%I64d", &a[i]);
		lo l = 0, r = i;
		while(l != r)
		{
			lo m = (l + r + 1) / 2;
			if(dp[m] >= a[i])
				l = m;
			else
				r = m - 1;
		}
		if(dp[l + 1] < a[i])
		{
			dp[l + 1] = a[i];
			is[l + 1] = i;
			fr[i] = is[l];
		}
	}
	for(lo i = MN - 1; i >= 0; i--)
	{
		if(dp[i] != -INF)
		{
			cout << i << endl;
			re(is[i]);
			return 0;
		}
	}
}

