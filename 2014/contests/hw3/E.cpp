
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
#define MN 8000000
#define sz(n) (lo) (n).size()
#define SM 32
#define DEB(...) fprintf(stderr,__VA_ARGS__)
const li INF = (1LL<<62) ;

using namespace std;


int main()
{
#ifdef MYLOCAL
   freopen("input.txt", "r", stdin);
  // freopen("perm.out", "w", stdout);
#else
    freopen("find2.in", "r", stdin);
    freopen("find2.out", "w",stdout);
#endif
    lo n, m;
    cin >> n>> m;
    set<lo> g;
    FOR(i, n)
    {
    	lo a;
    	scanf("%d", &a);
    	g.insert(a);
    }
    FOR(i, m)
    {
    	lo a;
    	scanf("%d", &a);
    	printf(g.count(a) ? "YES\n" : "NO\n");
    }
}
