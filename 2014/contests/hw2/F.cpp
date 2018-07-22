
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
//#include <unordered_map>
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
#define all(a) (a).begin(), (a).end()
#define pi 3.14159265358979323
#define eps 1e-9
#define MN 1010
#define sz(n) (lo) (n).size()
#define SM 32
#define DEB(...) fprintf(stderr,__VA_ARGS__)
const li INF = 2e9 + 1;

using namespace std;

void intr(lo &x, lo &y, lo &x2, lo &y2, lo X, lo Y, lo X2, lo Y2)
{
	x = max(x, X);
	x2 = min(x2, X2);
	y = max(y, Y);
	y2 = min(y2, Y2);
}
int main()
{
#ifdef MYLOCAL
   freopen("input.txt", "r", stdin);
#else
    freopen("rect1.in", "r", stdin);
    freopen("rect1.out", "w", stdout);
#endif
    lo n;
    cin >> n;
    lo X = -INF, X2 = INF, Y = -INF, Y2 = INF;
    FOR(i, n)
    {
    	lo x, x2, y, y2;
    	scanf("%d%d%d%d", &x, &y, &x2, &y2);
    	intr(X, Y, X2, Y2, x, y, x2, y2);
    }
    cout << max(0, X2 - X) * 1LL * max(0, Y2 - Y);
}
