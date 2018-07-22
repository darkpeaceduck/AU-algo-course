
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
//#define all(a) (a).begin(), (a).end()
#define DEB(...) fprintf(stderr,__VA_ARGS__)
#define pi 3.14159265358979323
//#define eps 1e-3
#define MN 10010
#define sz(n) (lo) (n).size()
#define SM 40
const li INF = 2e9;


using namespace std;

pair<lo, lo> last[MN], nex[MN];
void clear()
{
	FOR(i, MN)
	{
		nex[i] = mp(INF, INF);
	}
}

pair<lo, lo> upd(pair<lo, lo> fr, lo t, lo a)
{
	fr.second += a;
	if(fr.second > t)
	{
		fr.first++;
		fr.second = a;
	}
	return fr;
}
int main(){
#ifdef MYLOCAL
     //freopen("perm.ou t", "w", stdout);
    freopen("input.txt", "r", stdin);
#else
    freopen("ship.in", "r", stdin);
    freopen("ship.out", "w",stdout);
#endif
    lo t, n;
    cin >> t >> n;
    vector<lo> a(n);
    FOR(i ,n)
    {
    	scanf("%d", &a[i]);
    }
    last[0] = mp(1, 0);
    for(lo i = n; i > 1; i--)
    {
    	clear();
     	for(lo j = 0; j + i - 1 < n; j++)
    	{
    		nex[j + 1] = min(nex[j + 1], upd(last[j], t, a[j]));
			nex[j ] = min(nex[j], upd(last[j], t, a[j + i - 1]));
    	}
    	FOR(j, MN)
    		last[j] = nex[j];
    }
    lo ans = INF;
    FOR(i, n)
    {
    	pair<lo, lo> final = upd(last[i], t, a[i]);
    	ans = min(ans, final.first);
    }
    cout << ans ;
}
