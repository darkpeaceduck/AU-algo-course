
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
#define eps 1e-7
#define MN 1010
#define sz(n) (lo) (n).size()
#define SM 40
const li INF = 2e9;

using namespace std;

lo g[MN][MN];
int main()
{
#ifdef MYLOCAL
     //freopen("perm.ou t", "w", stdout);
    freopen("input.txt", "r", stdin);
#else
    freopen("incident.in", "r", stdin);
    freopen("incident.out", "w",stdout);
#endif
    lo n, m;
    cin >> n >> m;
    vector<pair<lo, lo> > edge(m);
    FOR(i, m)
    {
    	lo a, b;
    	cin >> a >> b;
    	a--;
    	b--;
    	g[a][b] = g[b][a] = 1;
    	edge[i] = mp(a, b);
    }
    FOR(i, n)
    {
    	FOR(j, m)
		{
    		printf("%d ", edge[j].first == i || edge[j].second == i);
		}
    	printf("\n");
    }
}