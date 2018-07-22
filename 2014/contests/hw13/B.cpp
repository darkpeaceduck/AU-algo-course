
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
lo p[MN];

lo find(lo a)
{
	return p[a] == a ? a : p[a] = find(p[a]);
}

bool unite(lo a, lo b)
{
	a  = find(a);
	b = find(b);
	if(a == b)
		return false;
	p[a] = b;
	return true;
}
int main()
{
#ifdef MYLOCAL
     //freopen("perm.ou t", "w", stdout);
    freopen("input.txt", "r", stdin);
#else
    freopen("spantree2.in", "r", stdin);
    freopen("spantree2.out", "w",stdout);
#endif
    lo n, m;
    cin >> n >> m;
    vector<pair<lo, pair<lo, lo> > > edge;
    FOR(i, m)
    {
    	lo a, b, c;
    	scanf("%d%d%d", &a, &b, &c);
    	a--; b--;
    	edge.pb(mp(c, mp(a, b)));
    }
    FOR(i, n)
    	p[i] = i;
    sort(edge.begin(), edge.end());
    li sum = 0;
    FOR(i, sz(edge))
    {
    	lo c = edge[i].first;
    	lo a = edge[i].second.first;
    	lo b = edge[i].second.second;
    	if(unite(a, b))
    		sum += c;
    }
    cout << sum;
}
