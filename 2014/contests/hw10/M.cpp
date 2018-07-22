
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

vector < vector<int> > g, gt;
vector<bool> used;
vector<int> order, comp, ans;

void dfs1 (int v) {
	used[v] = true;
	for (size_t i=0; i<g[v].size(); ++i) {
		int to = g[v][i];
		if (!used[to])
			dfs1 (to);
	}
	order.push_back (v);
}

void dfs2 (int v, int cl) {
	comp[v] = cl;
	for (size_t i=0; i<gt[v].size(); ++i) {
		int to = gt[v][i];
		if (comp[to] == -1)
			dfs2 (to, cl);
	}
}

bool sat2(lo n)
{

	used.assign (n, false);
	for (int i=0; i<n; ++i)
		if (!used[i])
			dfs1 (i);

	comp.assign (n, -1);
	for (int i=0, j=0; i<n; ++i) {
		int v = order[n-i-1];
		if (comp[v] == -1)
			dfs2 (v, j++);
	}

	for (int i=0; i<n; ++i)
		if (comp[i] == comp[i^1]) {
			return false;
		}

	ans.resize(n);
	for (int i=0; i<n; ++i) {
		ans[i] = comp[i] < comp[i^1] ? i : i^1;
//		cout << ans[i] << endl;
	}
	return true;
}

int main()
{
#ifdef MYLOCAL
     //freopen("perm.ou t", "w", stdout);
    freopen("input.txt", "r", stdin);
#else
    freopen("color.in", "r", stdin);
    freopen("color.out", "w",stdout);
#endif
    map<char, int>ise;
   ise['R'] = 0;
   ise['G'] = 1;
   ise['B'] = 2;
   char reise[3] = {'R', 'G', 'B'};
    lo n, m;
    cin >> n >> m;
    vector<lo> color(n);

    FOR(i, n)
    {
    	char c;
    	cin >> c;
    	color[i] = ise[c];
    }
    g.resize(n * 2);
    gt.resize(n * 2);
    FOR(i, m)
    {
    	lo a, b;
    	scanf("%d%d", &a, &b);
    	a--;
    	b--;
    	vector<lo> ina, inb;
    	FOR(j, 3)
    	{
    		if(color[a] != j)
    		{
    			ina.pb(j);
//    			cout << a << " " << j << endl;
    		}
			if(color[b] != j)
			{
    			inb.pb(j);
//    			cout << b << " " << j << endl;
			}
    	}
    	FOR(j, 2) FOR(k, 2)
		{
    		if(ina[j] == inb[k])
    		{
    			lo posa = a * 2 + j;
    			lo posb = b * 2 + k;
//    			printf("%d %d %d %d\n", a, 1^posa, b, posb);
//    			printf("%d %d %d %d\n", b, 1^posb, a, posa);
    			g[1 ^ posa].pb(posb);
    			g[1 ^ posb].pb(posa);
    			gt[posa].pb(1 ^ posb);
    			gt[posb].pb(1 ^ posa);
    		}
		}
    }
    if(!sat2(n * 2))
    	cout << "Impossible";
    else
    {
    	FOR(i, n)
		{
    		vector<lo> ina;
    		FOR(j, 3)
			{
				if(color[i] != j)
					ina.pb(j);
			}
    		printf("%c", reise[ina[ans[i * 2] - i * 2]]);
		}
    }
}
