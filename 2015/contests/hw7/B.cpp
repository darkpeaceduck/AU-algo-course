
#include <bits/stdc++.h>
#include <unordered_map>
#include <initializer_list>
#include <memory>
#include <vector>
#define mp make_pair
#define pb push_back
#define lo int
#define li long long int
#define db double

#define sz(a) (lo)(a).size()
#define FOR(i, n) for(int i = 0; i < (n); i++)
#define all(a) (a).begin(), (a).end()
using namespace std;
#define DEB(...) fprintf(stderr, __VA_ARGS__)

//=======================
//#define pi 3.14159265358979323
#define eps 1e-9
#define INF 2e9
#define MN 200
#define SM 2000
//========================

struct edge
{
	lo to, flow, maxflow, re, id;
	edge(lo to, lo flow, lo maxflow, lo re, lo id):to(to), id(id), flow(flow), maxflow(maxflow), re(re){};
	edge(){};
};
vector<vector<edge> > g;
void add_edge(lo v, lo to, lo maxflow, lo id)
{
	lo sz = g[v].size(), sz2 = g[to].size();
	g[v].push_back(edge(to, 0, maxflow, sz2, id));
	g[to].push_back(edge(v, 0, maxflow, sz, id));
}
lo d[MN], ids[MN];
bool bfs(lo id, lo st, lo x)
{
	lo n = (lo) g.size();
	for(lo i = 0; i < n; i++)
	{
		d[i] = -1;
	}
	queue<lo> q;
	q.push(id);
	d[id] = 0;
	while(!q.empty())
	{
		lo now = q.front();
		q.pop();
		for(lo i = 0; i < (lo) g[now].size(); i++)
		{
			if(g[now][i].maxflow - g[now][i].flow < x) continue;
			lo to = g[now][i].to;
			if(d[to] == -1)
			{
				d[to] = d[now] + 1;
				q.push(to);
			}
		}
	}
	return d[st] != -1;
}
lo dfs(lo id, lo st, lo x, lo flow)
{
	if(!flow) return 0;
	if(id == st) return flow;
	for(; ids[id] < (lo) g[id].size(); ids[id]++)
	{
		lo i = ids[id], to = g[id][i].to;
		if(g[id][i].maxflow - g[id][i].flow < x || d[to] != d[id] + 1) continue;
		lo is = dfs(to, st, x, min(flow, g[id][i].maxflow - g[id][i].flow));
		if(is)
		{
		   g[id][i].flow += is;
		   g[to][g[id][i].re].flow -= is;
		   return is;
		}
	}
	return 0;
}
lo try_din(lo s, lo t)
{
	lo ans = 0;
	for(lo x = (1<<25); x > 0; x /= 2)
	{
		if(!bfs(s, t, x)) continue;
		for(lo i = 0; i < (lo) g.size(); i++)
		{
			ids[i] = 0;
		}
		while(true)
		{
			lo te = dfs(s, t, x, INF);
			ans += te;
			if(!te)
			{
				x*= 2;
				break;
			}
		}
	}
	return ans;
}

int used[MN];
void dfs(int id){
	used[id] = 1;
	for(auto to : g[id]){
		if(!(to.maxflow && to.maxflow == to.flow) && !used[to.to])
		dfs(to.to);
	}
}

void dfs2(int id, vector<int> &ans){
	used[id] = 2;
	for(auto to : g[id]){
		if(!(to.maxflow && to.maxflow == to.flow) && used[to.to] != 2)
			dfs2(to.to, ans);
		if(!used[to.to])
			ans.pb(to.id);
	}
}
int main()
{
#ifdef MYLOCAL
    freopen("input.txt", "r", stdin);
 //   freopen("A9.out", "w", stdout);
#else
    freopen("cut.in", "r", stdin);
    freopen("cut.out", "w", stdout);
#endif
    int n, m;
	cin >> n >> m;
	g.resize(n);
	FOR(i, m){
		db a, b, c;
		cin >> a >> b >> c;
		a--;
		b--;
		add_edge(a, b, c, i + 1);
	}
	int res = try_din(0, n -1);
	vector<int> ans;
	dfs(0);
	dfs2(0, ans);
	sort(all(ans));
	cout << sz(ans) << " " << res << endl;
	copy(all(ans), ostream_iterator<int>(cout, " "));
};
