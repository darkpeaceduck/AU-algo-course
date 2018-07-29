
#include <bits/stdc++.h>
#include <unordered_map>
#include <initializer_list>
#include <memory>
#include <vector>
#define mp make_pair
#define pb push_back
#define lo long long int
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
#define INF (1LL<<62)
#define MN 1010
#define SM 2000
//=====================================================

struct edge
{
	lo val, flow, to, ret, maxflow, id;
	edge(lo to, lo val, lo maxflow, lo ret, lo id) : id(id), val(val), maxflow(maxflow), ret(ret), to(to), flow(0){};
	edge(){};
};
vector<vector<edge> > g;
vector<lo> pot;
void add_edge(lo from, lo to, lo flow, lo val, lo id)
{
	lo sz = g[from].size(), sz2 = g[to].size();
	g[from].push_back(edge(to, val, flow, sz2, id));
	g[to].push_back(edge(from, -val, 0, sz, id));
}
pair<lo, lo> levit(lo from, lo toto)
{
	vector<pair<lo, lo> > good(g.size(), mp(INF, 0)),par(g.size(), mp(-1, -1));
	vector<lo> used(g.size(), 0);
	good[from] = mp(0, INF);
	deque<lo> ag;
	ag.push_back(from);
	pair<lo, lo> with;
	while(!ag.empty())
	{
		lo now = ag.front(), flow = good[now].second, add = good[now].first, to;
		ag.pop_front();
		used[now] = 2;
		if(!flow) continue;
		for(lo i = 0; i < g[now].size(); i++)
		{
			to = g[now][i].to;
			if(g[now][i].flow >= g[now][i].maxflow) continue;
			with = mp(add + g[now][i].val,min(flow, g[now][i].maxflow - g[now][i].flow));
			if(with.first < good[to].first)
			{
				good[to] = with;
				par[to] = mp(now, i);
				if(used[to] == 2)
					ag.push_front(to);
				if(used[to] == 0)
					ag.push_back(to);
				used[to] = 1;
			}
		}
	}
	if(par[toto].first == -1) return mp((lo) -1, (lo) -1);
	lo flow = good[toto].second, now = toto, a, b;
	now = toto;
	lo cost = 0;
	while(par[now].first != -1)
	{
		a = par[now].first, b = par[now].second;
		g[a][b].flow += flow;
		cost += g[a][b].val * flow;
		b = g[a][b].ret;
		a = now;
		g[a][b].flow -= flow;
		now = par[now].first;
	}
	return mp(flow, cost);
}
pair<lo, lo> try_mincost(lo from, lo toto)
{
	lo flow = 0, val, ans = 0;
	while(true)
	{
		pair<lo, lo> temp =  levit(from, toto);
		if(temp.first == -1) break;
		flow += temp.first;
		ans += temp.second;
	}
	return mp(flow, ans);
}

void dfs(int id, int to, vector<int> &ans, bool yep = false){
	if(id == to){
		printf("%d ", sz(ans));
		for_each(all(ans), [](int w){printf("%d ", w );});
		printf("\n");
		return;
	}
	for(auto &ed : g[id]){
		if(ed.flow == 1 && ed.to <= to){
			ed.flow = 0;
			ans.pb(ed.id);
			dfs(ed.to, to, ans);
			ans.pop_back();
			if(!yep)
				break;
		}
	}
}

int main()
{
#ifdef MYLOCAL
    freopen("input.txt", "r", stdin);
   // freopen("output.txt", "w", stdout);
#else
    freopen("brides.in", "r", stdin);
    freopen("brides.out", "w", stdout);
#endif
    int n, m, k;
    cin >> n >> m >> k;
    g.resize(n + 1);
    FOR(i, m){
    	int a, b, d;
    	scanf("%d%d%d", &a, &b, &d);
    	a--;
    	b--;
    	add_edge(a, b, 1, d, i + 1);
    	add_edge(b, a, 1, d, i + 1);
    }
    add_edge(n, 0, k, 0, -1);
    pair<lo, lo> res = try_mincost(n, n - 1);
    if(res.first < k){
    	cout << -1;
    	return 0;
    }
    cout << fixed << setprecision(10) << (db)res.second / (db)k << endl;
    vector<int> temp;
    dfs(0, n - 1, temp, true);
}


