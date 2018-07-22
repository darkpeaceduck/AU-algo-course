
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
#define DEB(...) fprintf(err,__VA_ARGS__)
#define pi 3.14159265358979323
#define eps 1e-3
#define MN 300100
#define sz(n) (lo) (n).size()
#define SM 310
const li INF = 2e9;


using namespace std;

vector<pair<lo, lo> > g[MN];
lo val[MN];
lo ho[MN];
pair<lo, lo> fr[MN];
bool used[MN];
void dfs(lo id, lo n)
{
	used[id] = true;
	FOR(i, sz(g[id]))
	{
		lo to = g[id][i].second;
		if(!used[to] && val[to] == val[id] - 1)
			dfs(to, n);
	}
}
int main(){
#ifdef MYLOCAL
	 //freopen("perm.out", "w", stdout);
	freopen("input.txt", "r", stdin);
#else
	freopen("ideal.in", "r", stdin);
	freopen("ideal.out", "w",stdout);
#endif


	lo n, m;
	cin >> n >> m;
	FOR(i, n)
	{
		val[i] = INF;
		ho[i] = INF;
		fr[i] = mp(-1, -1);
	}

	FOR(i, m)
	{
		lo a,b, c;
		scanf("%d%d%d", &a, &b, &c);
		a--;
		b--;
		g[a].pb(mp(c, b));
		g[b].pb(mp(c, a));
	}
	FOR(i, n)
	{
		sort(g[i].begin(), g[i].end());
	}
	val[0] = 0;
	queue<lo> q;
	q.push(0);
	while(!q.empty())
	{
		lo id = q.front();
		q.pop();
		FOR(i, sz(g[id]))
		{
			lo to = g[id][i].second;
			if(val[to] > val[id] + 1)
			{
				val[to] = val[id] + 1;
				q.push(to);
			}
		}
	}

	dfs(n - 1, n);
	ho[0] = 0;
	vector<lo> v;
	v.pb(0);
	if(val[n - 1] == INF)
	{
		cout << "DNIWE";
		return 0;
	}
	FOR(q, val[n - 1])
	{
		map<lo, vector<lo> > good;
		FOR(i, sz(v))
		{
			lo id = v[i];
			FOR(j, sz(g[id]))
			{
				lo color = g[id][j].first;
				lo to = g[id][j].second;
				if(val[to] == val[id] + 1 && ho[to] > color)
				{
					good[color].pb(to);
					ho[to] = color;
					fr[to] = mp(id, color);
				}
			}
		}
		for(map<lo, vector<lo> >::iterator it = good.begin(); it != good.end(); it++)
		{
			bool ya = false;
			FOR(i, sz(it->second))
			{
				lo to = it->second[i];
				if(used[to])
					ya= true;
			}
			if(ya)
			{
				v = it->second;
				break;
			}
		}
	}
	vector<lo> outp;
	lo now = n - 1;
	while(now != -1)
	{
		outp.pb(fr[now].second);
		now = fr[now].first;
	}
	outp.pop_back();
	reverse(outp.begin(), outp.end());
	cout << sz(outp) << endl;
	FOR(i, sz(outp))
	{
		printf("%d ", outp[i]);
	}
}
