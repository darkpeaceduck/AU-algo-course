
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
#define SM 40
const li INF = 2e9;

using namespace std;


lo marked[MN];
lo unmarked[MN];

int main(){
#ifdef MYLOCAL
     //freopen("perm.ou t", "w", stdout);
    freopen("input.txt", "r", stdin);
#else
    freopen("marked2.in", "r", stdin);
    freopen("marked2.out", "w",stdout);
#endif
    lo n, x, y;
    cin >> n >> x >> y;
    FOR(i, x)
    {
    	lo k;
    	cin >> k;
    	lo mask = 0;
    	FOR(j, k)
    	{
    		lo a;
    		cin >> a;
    		a--;
    		mask |= (1<<a);
    	}
    	marked[mask]++;
    }
    for(lo i = (1<<n) - 1; i >= 0; i--)
    {
    	if(marked[i])
    	{
    		lo with = i;
    		while(with)
    		{
    			lo cur = (with & ((~with) + 1));
    			marked[i ^ cur]++;
    			with ^= cur;
    		}
    	}
    }
    FOR(i, y)
    {
    	lo k;
    	cin >> k;
    	lo mask = 0;
    	FOR(j, k)
    	{
    		lo a;
    		cin >> a;
    		a--;
    		mask |= (1<<a);
    	}
    	unmarked[mask]++;
    }
    lo ans = 0;
    for(lo i = (1<<n) - 1; i >= 0; i--)
    {
    	if(unmarked[i])
		{
    		marked[i] = 0;
    		lo with = i;
			while(with)
			{
				lo cur = (with & ((~with) + 1));
				unmarked[i ^ cur]++;
				with ^= cur;
			}
		}
    	ans += (marked[i] > 0);
    }
    cout << ans;
}


