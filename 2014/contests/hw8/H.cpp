
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
#define li unsigned long long int
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

lo all = 0;
lo mod = 1e9 + 7;
lo dp[MN];
lo add(li a, li b)
{
	return (a + b) % mod;
}
int main(){
#ifdef MYLOCAL
	 //freopen("perm.ou	t", "w", stdout);
	freopen("input.txt", "r", stdin);
#else
	freopen("distinct.in", "r", stdin);
	freopen("distinct.out", "w",stdout);
#endif
	memset(dp, -1, sizeof dp);
	lo n;
	cin >> n;
	FOR(i, n)
	{
		lo a;
		scanf("%d", &a);
		if(dp[a] == -1)
		{
			dp[a] = all;
			all = add(all, all + 1);
		}
		else
		{
			lo sum = add(all, mod - dp[a]);
			dp[a] = all;
			all = add(all, sum);
		}
	}
	cout << all;
}

