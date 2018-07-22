
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


int main(){
#ifdef MYLOCAL
    freopen("input.txt", "r", stdin);
     //freopen("perm.out", "w", stdout);
#else
    freopen("segments.in", "r", stdin);
    freopen("segments.out", "w",stdout);
#endif
    lo n, m;
    cin >> n >> m;
    vector<pair<lo, pair<lo, lo > > > good;
    vector<lo> ans(m);
    FOR(i, n)
    {
    	lo x, y;
    	scanf("%d%d", &x, &y);
    	if(x > y)
    		swap(x, y);
    	good.pb(mp(x, mp(0, -1)));
    	good.pb(mp(y, mp(2, -1)));
    }
    FOR(i, m)
    {
    	lo x;
    	scanf("%d", &x);
    	good.pb(mp(x, mp(1, i)));
    }
    sort(good.begin(), good.end());
    lo cnt = 0;
    FOR(i, sz(good))
    {
    	lo t = good[i].second.first;
    	lo id = good[i].second.second;
    	if(t == 0)
    		cnt++;
    	else if(t == 1)
    	{
    		ans[id] = cnt;
    	}
    	else
    	{
    		cnt--;
    	}
    }
    FOR(i, m)
    {
    	printf("%d ", ans[i]);
    }
}
