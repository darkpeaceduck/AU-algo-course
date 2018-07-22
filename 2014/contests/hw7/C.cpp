
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

lo dp[MN];
int main(){
#ifdef MYLOCAL
	freopen("input.txt", "r", stdin);
	 //freopen("perm.out", "w", stdout);
#else
	freopen("nails.in", "r", stdin);
	freopen("nails.out", "w",stdout);
#endif
	lo n;
	cin >> n;
	vector<lo> op(n);
	FOR(i, n)
		cin >> op[i];
	sort(op.begin(), op.end());
	FOR(i, MN)
		dp[i] = INF;
	dp[0] = 0;
	FOR(i, n)
	{
		for(lo j = i + 1; j < n; j++)
		{
			dp[j + 1] = min(dp[j + 1], dp[i] + op[j] - op[i]);
		}
	}
	cout << dp[n];
}
