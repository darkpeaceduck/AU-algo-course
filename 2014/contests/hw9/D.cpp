
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

lo mine[MN];
int main(){
#ifdef MYLOCAL
     //freopen("perm.ou t", "w", stdout);
    freopen("input.txt", "r", stdin);
#else
    freopen("modsum2.in", "r", stdin);
    freopen("modsum2.out", "w",stdout);
#endif
    lo n;
    cin >> n;
    FOR(i, n)
    {
    	lo a;
    	cin >> a;
    	mine[1<<i] = a;
    }
    FOR(i, (1<<n))
    {
    	FOR(j, n)
		{
    		if(!(i & (1<<j)))
    		{
    			mine[i | (1<<j)] = mine[i] + mine[1<<j] ;
    		}
		}
    }
    li result = 0;
    for(lo i = 1; i < ((1<<n) - 1); i++)
    {
    	lo mask = ((1<<n) - 1) ^ i;
    	for(lo j = mask; j > 0; j = (j - 1) & mask)
    	{
    		result += mine[j] % mine[i];
    	}
    }
    cout << result;
}


