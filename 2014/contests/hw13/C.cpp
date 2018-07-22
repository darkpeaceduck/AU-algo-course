
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
    freopen("cutting.in", "r", stdin);
    freopen("cutting.out", "w",stdout);
#endif
    lo n, m, k;
    cin >> n >> m >> k;
    FOR(i, n)
    	p[i] = i;
    vector<pair<lo, pair<lo, lo> > > z(k);
    vector<pair<lo, lo> > edge;
    map<pair<lo, lo>, lo > q;
    FOR(i, m)
    {
    	lo a, b;
    	scanf("%d%d", &a, &b);
    	a--;
    	b--;
    	edge.pb(mp(a, b));
    }
    scanf("\n");
    char s[10];
    FOR(i, k)
    {
    	lo a, b;
    	scanf("%s%d%d", &s, &a, &b);
    	a--;
    	b--;
    	lo t = !(strcmp(s, "cut"));
    	z.pb(mp(t, mp(a, b)));
    	if(t)
    	{
    		q[mp(a, b)]++;
    		q[mp(b, a)]++;
    	}
    }
    reverse(z.begin(), z.end());
    FOR(i, sz(edge))
    {
    	lo a = edge[i].first;
    	lo b = edge[i].second;
    	if(!q.count(mp(a, b)))
    		unite(a, b);
    }
    vector<lo> ans;
    FOR(i, k)
    {
    	lo t = z[i].first;
    	lo a = z[i].second.first;
    	lo b = z[i].second.second;
    	if(t)
    		unite(a, b);
    	else
    		ans.pb(find(a) == find(b));
    }
    reverse(ans.begin(), ans.end());
    FOR(i , sz(ans))
    	printf("%s\n", ans[i] ? "YES" : "NO");
}
