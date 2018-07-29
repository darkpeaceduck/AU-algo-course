
#pragma comment(linker, "/STACK:100000000000000")
#include <stdio.h>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <stack>
#include <queue>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <sstream>
#include <string.h>
#include <cctype>
#include <cassert>
#include <ctime>
#include <fstream>
#include <functional>
#define mp make_pair
//#define pb push_back
#define lo int
#define li long long int
#define db double
#define FOR(i, n) for(lo i = 0; i < (n); i++)
#define pi 3.14159265358979323
#define eps 1e-4
#define MN 1050
#define sz(a) (lo) (a).size()
#define SM 1<<6
using namespace std;
const li INF = 2e9;
#define DEB(...) fprintf(stderr, __VA_ARGS__)


struct edge
{
	lo val, flow, to, ret, maxflow;
	edge(lo to, lo val, lo maxflow, lo ret) : val(val), maxflow(maxflow), ret(ret), to(to), flow(0){};
	edge(){};
};
vector<vector<edge> > g;
vector<lo> pot;
lo d[MN * MN];
lo delta[MN * MN];
lo used[MN * MN];
void add_edge(lo from, lo to, lo flow, lo val)
{
    delta[to]++;
	lo sz = g[from].size(), sz2 = g[to].size();
	g[from].push_back(edge(to, val, flow, sz2));
	g[to].push_back(edge(from, -val, 0, sz));
}

void dfs(lo id)
{
    used[id]++;
    FOR(i, (lo) g[id].size())
    {
        if(!g[id][i].maxflow)
            continue;
        lo to = g[id][i].to;
        delta[to]--;
        d[to] = min(d[to], d[id] + g[id][i].val);
        if(!delta[to] && !used[to])
            dfs(to);
    }
}
pair<lo, lo> good[MN * MN], par[MN * MN];


inline pair<lo, lo> try_deyk(lo from, lo toto)
{
   FOR(i, sz(g))
    {
        good[i] = mp(INF, 0);
        par[i] = mp(-1, -1);
        used[i] = 0;
    }
    good[from] = mp(0, INF);
	priority_queue<pair<lo, lo>, vector<pair<lo, lo>>, greater<pair<lo, lo>> > ag;
	ag.push(mp((lo)0, from));
	pair<lo, lo> with;
	while(!ag.empty())
	{
        lo now = ag.top().second, flow = good[now].second, add = good[now].first, to;
        bool fail = add != ag.top().first;
        ag.pop();
        if(fail)
        	continue;
		used[now] = 2;
		if(!flow) continue;
		for(lo i = 0; i < (lo)g[now].size(); i++)
		{
			to = g[now][i].to;
			if(g[now][i].flow >= g[now][i].maxflow) continue;
			with = mp(add + g[now][i].val + d[now] - d[to],min(flow, g[now][i].maxflow - g[now][i].flow));
			if(with.first < good[to].first)
			{
				good[to] = with;
                ag.push(mp(good[to].first, to));
				par[to] = mp(now, i);
				used[to] = 1;
			}
		}
    }
        for(lo i = 0; i < (lo) g.size(); i++)
        {
            d[i] = (good[i].first == INF ? 0 :d[i] +  good[i].first);
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
pair<lo, lo> try_mincost(lo from, lo toto, lo k)
{
    FOR(i, MN * MN)
    {
        d[i] = INF;
    }
    d[0] = 0;
    memset(used, 0, sizeof used);
    dfs(0);
    FOR(i, MN * MN)
    {
        if(d[i] == INF)
            d[i] = 0;
    }
	lo flow = 0, val, ans = 0;
	FOR(i, k)
    {
		pair<lo, lo> temp =  try_deyk(from, toto);
		if(temp.first <= 0) break;
		flow += temp.first;
		ans += temp.second;
        if(flow == k)
            break;
	}
	return mp(flow, ans);
}
int main()
{
#ifdef MYLOCAL
    freopen("input.txt", "r", stdin);
   // freopen("output.txt", "w", stdout);
#else
    freopen("schedule.in", "r", stdin);
    freopen("schedule.out", "w", stdout);
#endif
    lo n, k;
    cin >> n >> k;
    g.resize(2 * n + 3);
    vector<pair<lo, pair<lo, lo> > > temp(n);
    memset(delta, 0, sizeof delta);
    int real = 2 * n;
    int begin = real + 1;
    int end  = begin + 1;
    add_edge(real, begin, k, 0);
    FOR(i, n)
    {
        lo a, b, c;
        scanf("%d%d%d", &a, &b, &c);
//        cin >> a >> b >> c;
        int ini = 2 * i;
        int oti = ini + 1;
        add_edge(oti, end, 1, 0);
        add_edge(ini, oti, 1, -c);
        temp[i] = mp(a, mp(b, c));
    }
    vector<int> v(n);
    FOR(i, n){
    	v[i] = i;
    }
    sort(v.begin(),v.end(),[&temp](int a, int b){ return temp[a].first < temp[b].first || (temp[a].first == temp[b].first && a < b);});
    add_edge(begin, 2 * v[0], k, 0);
    FOR(i, n){
    	if(i < n - 1){
    		add_edge(2 * v[i] , 2 * v[i + 1] , k, 0);
    	}
    	lo f1 =  temp[v[i]].first + temp[v[i]].second.first - 1;
    	for(int j = i + 2; j < n; j++){
    		if(f1 < temp[v[j]].first){
    			add_edge(2 * v[i] + 1, 2 * v[j] , 1, 0);
    			break;
    		}
    	}
    }
    try_mincost(real, end, k);
    vector<lo> out(n);
    FOR(i, n){
    	for(auto ed : g[2 * i]){
    		if(ed.to == 2 * i + 1 && ed.flow){
    			out[i]++;
    		}
    	}
    }
    FOR(i, n)
    {
    	printf("%d ", (out[i]  > 0));
    }
}

