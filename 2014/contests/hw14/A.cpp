
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
#define MN 200000
#define sz(n) (lo) (n).size()
#define SM 40
const li INF = 2e9;

using namespace std;

//#include <memory>
//#include <pthread.h>
int main()
{
#ifdef MYLOCAL
     //freopen("perm.ou t", "w", stdout);
    freopen("input.txt", "r", stdin);
#else
    freopen("snowmen.in", "r", stdin);
    freopen("snowmen.out", "w",stdout);
#endif
    lo n;
    cin >> n;
    vector<lo> mass;
    vector<pair<lo, lo> > fr;
    mass.pb(0);
    fr.pb(mp(-1, 0));
    li sum = 0;
    FOR(i, n)
    {
    	lo t, m;
    	scanf("%d%d", &t, &m);
    	if(m)
    	{
    		fr.pb(mp(t, m));
    		mass.pb(mass[t] + m);
    	}
    	else
    	{
    		pair<lo, lo> last = fr[t];
    		if(last == mp(-1, 0))
    		{
    			mass.pb(0);
    			fr.pb(last);
    		}
    		else
    		{
    			mass.pb(mass[last.first]);
    			fr.pb(fr[last.first]);
    		}
    	}
    	sum += mass.back();
    }
    cout << sum;
}
