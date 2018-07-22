
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
#define all(a) (a).begin(), (a).end()
#define pi 3.14159265358979323
#define eps 1e-9
#define MN 10000
#define sz(n) (lo) (n).size()
#define SM 105 * 100
#define DEB(...) fprintf(stderr,__VA_ARGS__)
const li INF = 1e9 ;


using namespace std;

struct table
{
	vector<vector<pair<lo, lo> > > a;
	table(lo size)
	{
		a.resize(size);
	}
	lo get(lo el)
	{
		lo at = el % sz(a);
		FOR(i, sz(a[at]))
		{
			if(a[at][i].first == el)
				return a[at][i].second;
		}
		return -1;
	}
	void set(lo el, lo val)
	{
		lo at = el % sz(a);
		FOR(i, sz(a[at]))
		{
			if(a[at][i].first == el)
			{
				a[at][i].second = val;
				return;
			}
		}
		a[at].pb(mp(el, val));
	}
};
int main(){
#ifdef MYLOCAL
    freopen("input.txt", "r", stdin);
     //freopen("perm.out", "w", stdout);
#else
    freopen("swap.in", "r", stdin);
    freopen("swap.out", "w",stdout);
#endif
    lo mod = 99971;
    table q(mod);
    lo n;
    cin >> n;
    FOR(i, n)
    {
    	lo a, b;
    	scanf("%d%d", &a, &b);
    	lo ga = q.get(a);
    	lo gb = q.get(b);
    	if(ga == -1) ga = a;
    	if(gb == -1) gb = b;
    	printf("%d\n", abs(ga - gb));
    	q.set(a, gb);
    	q.set(b, ga);
    }
}
