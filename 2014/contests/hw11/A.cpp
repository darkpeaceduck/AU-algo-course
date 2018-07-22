
#pragma comment(linker, "/STACK:100000000000000")
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
#define MN 100100
#define sz(n) (lo) (n).size()
#define SM 40
const li INF = 2e9;

using namespace std;

#include <memory>


int main()
{
#ifdef MYLOCAL
     //freopen("perm.ou t", "w", stdout);
    freopen("input.txt", "r", stdin);
#else
    freopen("balls.in", "r", stdin);
    freopen("balls.out", "w",stdout);
#endif
    vector<lo> a;
    a.pb(1);
    lo maxi = 300100;
    for(int i = 2; a.back() <= maxi; i++)
    {
    	a.pb(a.back() + i);
    }
    vector<lo> b;
    b.pb(a[0]);
    for(int i = 1; b.back() <= maxi; i++)
    {
    	b.pb(b.back() + a[i]);
    }
    vector<lo> mini(maxi, INF);
    mini[0] = 0;
    FOR(i, sz(mini))
    {
    	FOR(j, sz(b))
		{
    		if(i + b[j] < sz(mini))
    		{
    			mini[i + b[j]] = min(mini[i + b[j]], mini[i] + 1);
    		}
		}
    }
    lo T;
    cin >> T;
    FOR(i, T)
    {
    	lo m;
    	cin >> m;
    	cout << mini[m] << endl;
    }
}
