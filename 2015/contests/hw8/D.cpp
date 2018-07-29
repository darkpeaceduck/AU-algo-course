
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
#define FORN(i, j, n) for(int i = (j); i < (n); i++)
#define all(a) (a).begin(), (a).end()
using namespace std;
#define DEB(...) fprintf(stderr, __VA_ARGS__)

//=======================
//#define pi 3.14159265358979323
#define eps 1e-9
#define INF 2e9
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

int a[MN][MN];
int main()
{
#ifdef MYLOCAL
    freopen("input.txt", "r", stdin);
   // freopen("output.txt", "w", stdout);
#else
    freopen("multiassignment.in", "r", stdin);
    freopen("multiassignment.out", "w", stdout);
#endif
    int n, k;
    cin >> n >> k;
    g.resize(2 * n + 3);
    int real =2 * n;
    int start = real + 1;
    int end = start + 1;
    FOR(i, n) FOR(j, n){
    	scanf("%d", &a[i][j]);
    }
    add_edge(real, start, k * n, 0, -1);
    FOR(i, n){
    	add_edge(start, i, k, 0, -1);
    	add_edge(n + i, end, k, 0, -1);
    }
	FOR(i, n) FOR(j, n){
		add_edge(i, n + j, 1, a[i][j], -1 );
	}
    cout << try_mincost(real, end).second << endl;
    memset(a, -1, sizeof a);
    FOR(i, n){
    	for(auto ed : g[i]){
    		if(ed.flow == 1){
    			a[i][ed.to % n] = ed.val;
    		}
    	}
    }
    FOR(q, k){
    	g.clear();
    	g.resize(2 * n + 3);
    	add_edge(real, start, n, 0, -1);
		FOR(i, n){
			add_edge(start, i, 1, 0, -1);
			add_edge(n + i, end, 1, 0, -1);
		}
		FOR(i, n) FOR(j, n){
			if(a[i][j] == -1)
				continue;
			add_edge(i, n + j, 1, 0, -1 );
		}
		try_mincost(real , end);
		FOR(i, n){
			for(auto ed : g[i]){
				if(ed.flow == 1){
					printf("%d ", ed.to % n + 1);
					a[i][ed.to % n] = -1;
				}
			}
		}
		printf("\n");
    }
}


