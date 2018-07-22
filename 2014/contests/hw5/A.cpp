
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
#define DEB(...) fprintf(stderr,__VA_ARGS__)
#define pi 3.14159265358979323
#define eps 1e-4
#define MN (1<<24)
#define sz(n) (lo) (n).size()
#define SM 1000100
const li INF = 1e9 ;


using namespace std;

unsigned int cur = 0,a, b;
unsigned int ra()
{
	cur = cur * a + b;
	return cur >> 8;
}
lo fen[SM], is[MN];
void inc(lo id)
{
	id = SM - 1 - id;
	for(; id < SM; id += (id + 1) & -(id + 1))
	{
		fen[id]++;
	}
}
lo geti(li id)
{
	id = SM - 1 - id - 1;
	lo res = 0;
	for(; id >= 0; id -= (id + 1) & -(id + 1))
	{
		res += fen[id];
	}
	return res;
}
int main(){
#ifdef MYLOCAL
    freopen("input.txt", "r", stdin);
     //freopen("perm.out", "w", stdout);
#else
    freopen("invcnt.in", "r", stdin);
    freopen("invcnt.out", "w",stdout);
#endif
    lo n, m;
    cin >> n >> m >> a >> b;
    li ans = 0;
    vector<lo> good(n), old(n);
    FOR(i, n)
    {
    	lo now = ra() % m;
//    	inc(now);
    	//cout << now << " ";
//    	ans += geti(now);
    	good[i] = now;
    	old[i] = now;
    }
    sort(good.begin(), good.end());
    good.resize(unique(good.begin(), good.end()) - good.begin());
    FOR(i, sz(good))
    {
    	is[good[i]] = i;
    }
    FOR(i, n)
    {
    	lo now = is[old[i]];
    	inc(now);
    	ans += geti(now);
    }
    cout << ans;
}
