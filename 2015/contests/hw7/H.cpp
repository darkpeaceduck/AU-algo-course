
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

//=======================
int sign(int a){
	if(a > 0)
		return 1;
	if(a < 0)
		return -1;
	return 0;
}
//========================
vector<int> g[MN],
			gr[MN];
int w[MN];
int is_comp[MN];
vector<bool> used;
vector<int> order;
int color = 0;

void dfs1 (int v) {
	used[v] = true;
	for (size_t i=0; i<g[v].size(); ++i)
		if (!used[ g[v][i] ])
			dfs1 (g[v][i]);
	order.push_back (v);
}

void dfs2 (int v) {
	is_comp[v] = color;
	used[v] = true;
	for (size_t i=0; i<gr[v].size(); ++i)
		if (!used[ gr[v][i] ])
			dfs2 (gr[v][i]);
}

void count_weights(int n){
	used.assign (n, false);
	for (int i=0; i<n; ++i)
		if (!used[i])
			dfs1 (i);
	used.assign (n, false);
	reverse(all(order));
	for (int i=0; i<n; ++i) {
		int v = order[i];
		if (!used[v]) {
			color++;
			dfs2 (v);
		}
	}

	//OK, now lets count
	for(int i = n - 1; i >= 0; i--){
		int delta = 0;
		for(int j = sz(g[i]) - 1; j >= 0; j--){
			int to = g[i][j];
			if(is_comp[i] == is_comp[to]){
				delta++;
				swap(g[i][j], g[i].back());
			} else {
//				w[i] += w[to];
			}
		}
		FOR(j, delta){
			g[i].pop_back();
		}
	}
}
//=========================
struct edge
{
	lo val, flow, to, ret, maxflow;
	edge(lo to, lo val, lo maxflow, lo ret) : val(val), maxflow(maxflow), ret(ret), to(to), flow(0){};
	edge(){};
};
struct edGe
{
	lo to, flow, maxflow, re;
	edGe(lo to, lo flow, lo maxflow, lo re):to(to), flow(flow), maxflow(maxflow), re(re){};
	edGe(){};
};
vector<vector<edGe> > G;
void add_edGe(lo v, lo to, lo maxflow)
{
	lo sz = G[v].size(), sz2 = G[to].size();
	G[v].push_back(edGe(to, 0, maxflow, sz2));
	G[to].push_back(edGe(v, 0, 0, sz));
}
lo d[MN], ids[MN];
bool bfs(lo id, lo st, lo x)
{
	lo n = (lo) G.size();
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
		for(lo i = 0; i < (lo) G[now].size(); i++)
		{
			if(G[now][i].maxflow - G[now][i].flow < x) continue;
			lo to = G[now][i].to;
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
	for(; ids[id] < (lo) G[id].size(); ids[id]++)
	{
		lo i = ids[id], to = G[id][i].to;
		if(G[id][i].maxflow - G[id][i].flow < x || d[to] != d[id] + 1) continue;
		lo is = dfs(to, st, x, min(flow, G[id][i].maxflow - G[id][i].flow));
		if(is)
		{
		   G[id][i].flow += is;
		   G[to][G[id][i].re].flow -= is;
		   return is;
		}
	}
	return 0;
}
lo try_din(lo s, lo t)
{
	lo ans = 0;
	for(lo x = (1LL << 25); x > 0; x /= 2)
	{
		if(!bfs(s, t, x)) continue;
		for(lo i = 0; i < (lo) G.size(); i++)
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
//=========================
int solve(){
	int n;
	cin >> n;
	FOR(i, n){
		scanf("%d", &w[i]);
	}
	FOR(i, n){
		int SZ;
		cin >> SZ;
		g[i].resize(SZ);
		FOR(j, SZ){
			scanf("%d", &g[i][j]);
			g[i][j]--;
		}
	}

	count_weights(n);
	G.resize(n + 2);
	int sum = 0;
	FOR(i, n){
		if(w[i] > 0){
			add_edGe(0, i + 1, w[i]);
			sum += w[i];
		} else{
			add_edGe(i + 1, sz(G) - 1, -w[i]);
		}
		for(auto to : g[i]){
				add_edGe(i + 1, to + 1, INF);
			}
 	}
	int val = try_din(0, sz(G) - 1);
	//
//		FOR(i, n){
//			DEB("%d ", w[i]);
//		}
//		FOR(i, n){
//			for(auto to : G[i]){
//				if(to.flow)
////				DEB("%d %d : %d\n", i, to.to, to.flow);
//			}
//		}
	return sum - val;
}
int main()
{
#ifdef MYLOCAL
    freopen("input.txt", "r", stdin);
 //   freopen("A9.out", "w", stdout);
#else
    freopen("matan.in", "r", stdin);
    freopen("matan.out", "w", stdout);
#endif
    cout << solve();
};
