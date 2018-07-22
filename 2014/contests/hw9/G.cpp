
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
#define MN 1<<22
#define sz(n) (lo) (n).size()
#define SM 22
const li INF = 2e9;

using namespace std;

lo dp[MN], go[MN];
lo n,m ;
void re(lo a, lo en)
{
	FOR(j, n)
	{
		if((dp[a] & (1<<j)) && (go[1<<j] & (1<<en)))
		{
			re(a ^ (1<<j),j);
			break;
		}
	}
	cout << en + 1 << " ";
}
int main(){
#ifdef MYLOCAL
     //freopen("perm.ou t", "w", stdout);
    freopen("input.txt", "r", stdin);
#else
    freopen("path.in", "r", stdin);
    freopen("path.out", "w",stdout);
#endif

    cin >> n >> m;
    FOR(i, m)
    {
    	lo a, b;
    	cin >> a >> b;
    	a--;
    	b--;
    	if(a == b)
    		continue;
    	go[1<<a] |= (1<<b);
    }
    FOR(i, n)
    {
    	dp[1<<i] |= (1<<i);
    }
    lo ans = 0;
    lo val = 0;
    FOR(i, (1<<n))
    {
    	lo mask = dp[i];
    	lo one = 0;
    	FOR(j, n)
    	{
    		if(i & (1<<j))
    			one++;
    		else
    		{
    			go[i | (1<<j)] |= go[i];
				if(go[mask] & (1<<j))
				{
					dp[i | (1<<j)] |= (1<<j);
				}
    		}
    	}
    	if(dp[i])
    	{
    		if(val < one)
    		{
    			val = one;
    			ans = i;
    		}
    	}
    }
    cout << val - 1 << endl;
    FOR(j, n)
    {
    	if(dp[ans] & (1<<j))
    	{
    		re(ans ^ (1<<j), j);
    		break;
    	}
    }
}


