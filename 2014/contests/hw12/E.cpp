
//#pragma comment(linker, "/STACK:100000000000000")
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
#define all(a) (a).begin(), (a).end()
#define DEB(...) fprintf(stderr,__VA_ARGS__)
#define pi 3.14159265358979323
#define eps 1e-7
#define MN 200
#define sz(n) (lo) (n).size()
#define SM 40
const li INF = 2e9;

using namespace std;

//#include <memory>
//#include <pthread.h>
lo d[MN][MN];
int main()
{
#ifdef MYLOCAL
     //freopen("perm.ou t", "w", stdout);
    freopen("input.txt", "r", stdin);
#else
    freopen("diameter.in", "r", stdin);
    freopen("diameter.out", "w",stdout);
#endif
    lo n;
    cin >> n;
    FOR(i, n) FOR(j, n)
		{
    		scanf("%d", &d[i][j]);
    		if(d[i][j] == -1)
    			d[i][j] = INF;
		}
    FOR(k, n) FOR(i, n) FOR(j, n)
	{
    	if(d[i][k] != INF && d[k][j] != INF)
    		d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
	}
    lo outp = 0;
    lo outp2 = INF;
    FOR(i, n)
    {
    	lo vi = 0;
    	FOR(j, n)
		{
    		if(d[i][j] == INF)
    			continue;
    		outp = max(outp, d[i][j]);
    		vi = max(vi, d[i][j]);
		}
    	outp2 = min(outp2, vi);
    }
    cout << outp << endl << outp2;
}


