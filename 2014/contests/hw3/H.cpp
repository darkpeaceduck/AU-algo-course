
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
//#include <unordered_map>
//expr
/*#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
*/
//

#define mp make_pair
#define pb push_back
#define lo unsigned int
#define li unsigned long long int
#define db double
#define pb push_back
#define FOR(i, n) for(lo (i) = 0; (i) < (n); (i)++)
#define all(a) (a).begin(), (a).end()
#define pi 3.14159265358979323
#define eps 1e-9
#define MN 1<<24
#define sz(n) (lo) (n).size()
#define SM 32
#define DEB(...) fprintf(stderr,__VA_ARGS__)
const li INF = (1LL<<62) ;

using namespace std;

unsigned int cur = 0;
unsigned int ra24(lo a, lo b)
{
    cur = cur * a + b;
    return cur >> 8;
}
unsigned long long ra32(int A, int B)
{
    unsigned long long a = ra24(A, B), b = ra24(A, B);
    return (a << 8) ^ b;
}


int main()
{
#ifdef MYLOCAL
    freopen("input.txt", "r", stdin);
    // freopen("perm.out", "w", stdout);
#else
    freopen("linesum.in", "r", stdin);
    freopen("linesum.out", "w",stdout);
#endif
    lo m, q;
    cin >> m >> q;
    lo a, b;
    cin >> a >> b;
    vector<pair<li, li> > go(m);
    FOR(i, m)
    {
        li val = ra32(a, b);
        li x = ra32(a, b);
        go[i] = mp(x, val);
    }
  sort(go.begin(), go.end());
    vector<lo> sum(m  );
    sum[0] = go[0].second;
    for(lo i = 1; i < m; i++)
    {
        sum[i] = sum[i - 1] + go[i].second;
    }

    lo ans = 0;
    FOR(i, q)
    {
        li l = ra32(a, b);
        li r= ra32(a,b);
        if(l > r)
            swap(l, r);

//        /*
        if(go[0].first > r)
            continue;
        lo id = upper_bound(go.begin(), go.end(), mp(r, INF)) - go.begin();
        id--;
        lo id2 = upper_bound(go.begin(), go.end(), mp(l - 1, INF)) - go.begin();
        lo val = sum[id]  -  (id2 ? sum[id2 - 1] : 0);
        ans += val;

    }
  //  cout << ans2 << endl;
    cout << ans ;
}
