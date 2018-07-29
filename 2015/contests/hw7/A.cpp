
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
#define MN 200000
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
	g[to].push_back(edge(v, 0, 0, sz, id));
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
	for(lo x = 2; x > 0; x /= 2)
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


vector<int> ng[MN];
int used[MN];
bool dfs(int id, int s, int t, vector<int> &ans){
	ans.pb(id);
	if(id == t)
		return true;
	for(int i = sz(ng[id]) - 1; i>= 0; i--){
		if(dfs(ng[id][i], s, t, ans)){
			ng[id].pop_back();
			return true;
		}
	}
	ans.pop_back();
}
int main()
{
#ifdef MYLOCAL
    freopen("input.txt", "r", stdin);
 //   freopen("A9.out", "w", stdout);
#else
    freopen("snails.in", "r", stdin);
    freopen("snails.out", "w", stdout);
#endif
    int n, m, s, t;
	cin >> n >> m >> s >> t;
	g.resize(n + 1);
	add_edge(0, s, 2, -1);
	FOR(i, m){
		int a, b;
		scanf("%d%d", &a, &b);
		add_edge(a, b, 1, i);
	}
	int fl = try_din(0, t);
	if(fl < 2){
		cout << "NO";
	}else{
		cout << "YES" << endl;
		vector<int> temp;
		for(int i = 0; i < sz(g); i++){
			for(auto to : g[i]){
				if(to.flow == 1)
					ng[i].pb(to.to);
			}
		}
		FOR(i, 2){
			memset(used, 0, sizeof used);
			vector<int> ans;
			dfs(s, s, t, ans);
			for(auto id : ans){
				printf("%d ", id);
			}
			printf("\n");
		}

	}
};
