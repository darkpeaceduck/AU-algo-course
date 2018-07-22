
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
#define MN 1<<20
#define sz(n) (lo) (n).size()
#define SM 19
const li INF = 2e9;

using namespace std;

lo dp[MN], val[MN], mask[MN];
int main(){
#ifdef MYLOCAL
	 //freopen("perm.ou t", "w", stdout);
	freopen("input.txt", "r", stdin);
#else
	freopen("bottletaps.in", "r", stdin);
	freopen("bottletaps.out", "w",stdout);
#endif
	lo n;
	cin >> n;
	FOR(i, n)
	{
		cin >> val[i];
		mask[i] = (1<<i);
	}
	lo m;
	cin >> m;
	FOR(i, m)
	{
		cin >> val[i + n];
		lo need = 0;
		lo k;
		cin >> k;
		FOR(j, k)
		{
			lo a;
			cin >> a;
			a--;
			need |= (1<<a);
		}
		mask[i + n] = need;
	}
	m += n;
	lo res = 0;
	lo k;
	cin >> k;
	FOR(i, k)
	{
		lo a;
		cin >> a;
		a--;
		res |= (1<<a);
	}
	FOR(i, res + 1)
	{
		if(i)
			dp[i] = INF;
		FOR(j, m)
		{

			dp[i] = min(dp[i], dp[i ^ (i & mask[j])] + val[j]);
		}
	}

	cout << dp[res];
}


