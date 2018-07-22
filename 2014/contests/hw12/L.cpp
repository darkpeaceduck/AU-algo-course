
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
#include <fstream>
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
#define MN 10010
#define sz(n) (lo) (n).size()
#define SM 12
const li INF = 2e9;

using namespace std;

//#include <memory>
//#include <pthread.h>

vector<pair<lo, lo> > g[MN];
void ostov(lo A, vector<vector<lo> > &dest)
{
	lo n = sz(dest);
	vector<lo> mini(n, INF), fr(n, -1);
	FOR(i, n)
		dest[i].resize(3, 0);
	mini[A] = 0;
	set<pair<lo, lo> > q;
	q.insert(mp(mini[A], A));

	while(!q.empty())
	{
		lo id = q.begin()->second;
//		cerr << id << " " << mini[id] << endl;
		q.erase(q.begin());
		if(fr[id] != -1)
		{
			dest[id] = dest[fr[id]];
			dest[id].pb(mini[id]);
			sort(dest[id].begin(), dest[id].end());
			reverse(dest[id].begin(), dest[id].end());
			dest[id].resize(3);
		}
		FOR(i, sz(g[id]))
		{
			lo to = g[id][i].first;
			lo add = g[id][i].second;
			if(add < mini[to])
			{
				set<pair<lo, lo> >::iterator it = q.find(mp(mini[to], to));
				if(it != q.end())
					q.erase(it);
				mini[to] = add;
				fr[to] = id;
				q.insert(mp(mini[to], to));
			}
		}
	}
}
int main()
{
#ifdef MYLOCAL
//     freopen("perm.ou t", "w", stdout);
    freopen("input.txt", "r", stdin);
#else
    freopen("customs.in", "r", stdin);
    freopen("customs.out", "w",stdout);
#endif
    lo n, m;
    cin >> n >> m;
    vector<pair<pair<lo, lo>, lo> > edge;
    FOR(i, m)
    {
    	lo a, b, c;
    	cin >> a >> b >> c;
    	a--;
    	b--;
    	g[a].pb(mp(b, c));
    	g[b].pb(mp(a, c));
    	edge.pb(mp(mp(a, b), c));
    	edge.pb(mp(mp(b, a), c));
    }
    lo A, B;
    cin >> A >> B;
    A--;
    B--;
    vector<vector<lo> > d1(n), d2(n);
    ostov(A, d1);
    ostov(B, d2);
    li ans = 1e11;

    FOR(i, sz(edge))
    {
    	lo a = edge[i].first.first;
    	lo b = edge[i].first.second;
    	if(a != A && !d1[a][0])
    		continue;
    	if(b != B && !d2[b][0])
    		continue;
    	lo c = edge[i].second;
    	vector<lo> ok;
    	FOR(j, 3)
    	{
    		ok.pb(d1[a][j]);
    		ok.pb(d2[b][j]);
    	}
    	ok.pb(c);
    	sort(ok.begin(), ok.end());
    	reverse(ok.begin(), ok.end());
    	ok.resize(3);
    	ans = min(ans, ok[0] * 1LL + ok[1] + ok[2]);
    }
    cout << ans;
}

