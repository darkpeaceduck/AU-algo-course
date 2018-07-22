
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
#define MN 1010
#define sz(n) (lo) (n).size()
#define SM 40
const li INF = 2e9;

using namespace std;

//#include <memory>
//#include <pthread.h>

vector<pair<lo, lo> > g[MN];
lo vsz[MN];
lo up_edge[MN];
lo ptr[MN];
vector<vector<lo> > dp[MN];
vector<vector<pair<lo, lo> > > fr[MN];

void dfs(lo id, lo p)
{
	vsz[id] = 1;
	dp[id].resize(sz(g[id]) - (p != -1) + 2);
	fr[id].resize(sz(g[id]) - (p != -1) + 2);

	ptr[id] = 0;
	dp[id][0].resize(5, INF);
	fr[id][0].resize(5, mp(-1, -1));
	dp[id][0][1] = 0;

	FOR(i, sz(g[id]))
	{
		lo to = g[id][i].first;
		lo to_edge = g[id][i].second;
		if(to == p)
			continue;
		up_edge[to] = to_edge;
		dfs(to, id);
		ptr[id]++;
		dp[id][ptr[id]].resize(vsz[id] + vsz[to] + 2, INF);
		fr[id][ptr[id]].resize(vsz[id] + vsz[to] + 2, mp(-1, -1));
		for(lo j = vsz[id]; j >= 0; j--)
			for(lo k = 0; k <= vsz[to]; k++)
			{
				if(dp[to][ptr[to]][k] == INF)
					continue;
				if(dp[id][ptr[id]][j + k] > dp[id][ptr[id] - 1][j] + dp[to][ptr[to]][k])
				{
					dp[id][ptr[id]][j + k] = dp[id][ptr[id] - 1][j] + dp[to][ptr[to]][k];
					fr[id][ptr[id]][j + k] = mp(to, k);
				}
			}
		vsz[id] += vsz[to];
	}
	if(p !=-1)
	{
		dp[id][ptr[id]][0] = 1;
		fr[id][ptr[id]][0] = mp(-1, up_edge[id]);
	}
}

void make_result(lo a, lo p, lo b, vector<lo> &ans)
{
	if(p < 0 || b < 0)
		return;
	lo fra = fr[a][p][b].first;
	lo frb = fr[a][p][b].second;
	if(fra == -1)
	{
		if(frb != -1)
			ans.pb(frb);
	}
	else
	{
		make_result(fra, ptr[fra], frb, ans);
		make_result(a, p - 1, b - frb, ans);
	}
}

int main()
{
#ifdef MYLOCAL
     //freopen("perm.ou t", "w", stdout);
    freopen("input.txt", "r", stdin);
#else
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w",stdout);
#endif
    lo n, need;
    cin >> n >> need;
    FOR(i, n - 1)
    {
    	lo a, b;
    	scanf("%d%d", &a, &b);
//    	a  = 1;
//    	b = i + 2;
    	a--;
    	b--;
    	g[a].pb(mp(b, i + 1));
    	g[b].pb(mp(a, i + 1));
    }
    dfs(0, -1);
    lo ans = dp[0][ptr[0]][need];
    lo ans_vert = 0;
    FOR(i, n)
    {
    	if(sz(dp[i][ptr[i]]) <= need)
    		continue;
    	if(ans > dp[i][ptr[i]][need] + 1)
    	{
    		ans = dp[i][ptr[i]][need] + 1;
    		ans_vert = i;
    	}
    }
    vector<lo> outp;
    if(ans_vert)
    	outp.pb(up_edge[ans_vert]);
    make_result(ans_vert, ptr[ans_vert], need, outp);
    cout << sz(outp) << endl;
    FOR(i, sz(outp))
    	printf("%d ", outp[i]);
}


