
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
	lo to,  re, id;
	db flow, maxflow;
	edge(lo to, lo flow, db maxflow, lo re, lo id): id(id), to(to), flow(flow), maxflow(maxflow), re(re){};
	edge(){};
};
vector<vector<edge> > g;
void add_edge(lo v, lo to, db maxflow, lo id)
{
	lo sz = g[v].size(), sz2 = g[to].size();
	g[v].push_back(edge(to, 0, maxflow, sz2, id));
	g[to].push_back(edge(v, 0, 0, sz, -1));
}

lo d[MN];
lo ids[MN];
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

db dfs(lo id, lo st, lo x, db flow)
{
	if(!flow) return 0;
	if(id == st) return flow;
	for(; ids[id] < (lo) g[id].size(); ids[id]++)
	{
		lo i = ids[id], to = g[id][i].to;
		if(g[id][i].maxflow - g[id][i].flow < x || d[to] != d[id] + 1) continue;

		db is = dfs(to, st, x, min(flow, g[id][i].maxflow - g[id][i].flow));
		if(is)
		{
		   g[id][i].flow += is;
		   g[to][g[id][i].re].flow -= is;
		   return is;
		}
	}
	return 0;
}

db try_din(lo s, lo t)
{
	db ans = 0;
	int i = 200;
	for(db x = (1e9 + 1); i >= 0; x /= 2, i--)
	{
		if(!bfs(s, t, x)) continue;
		for(lo i = 0; i < (lo) g.size(); i++)
		{
			ids[i] = 0;
		}
		while(true)
		{
			db te = dfs(s, t, x, INF);
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

int main()
{
#ifdef MYLOCAL
    freopen("input.txt", "r", stdin);
 //   freopen("A9.out", "w", stdout);
#else
    freopen("flow2.in", "r", stdin);
    freopen("flow2.out", "w", stdout);
#endif
    int n, m;
    cin >> n >> m;
    g.resize(n);
    FOR(i, m){
    	db a, b, c;
    	cin >> a >> b >> c;
    	a--;
    	b--;
    	add_edge(a, b, c, i);
    }
    printf("%.10lf\n", try_din(0, n -1));
    vector<db> ans(m);
    for(auto id : g){
    	for(auto ed : id){
    		if(ed.id != -1)
    		ans[ed.id] = ed.flow;
    	}
    }
    for(auto an : ans){
    	printf("%.10lf\n", an);
    }
};
