
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
#define MN 11000
#define SM 2000
//=====================================================
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

char ma[200][200];
int main()
{
#ifdef MYLOCAL
    freopen("input.txt", "r", stdin);
   // freopen("output.txt", "w", stdout);
#else
    freopen("drawing.in", "r", stdin);
    freopen("drawing.out", "w", stdout);
#endif
    int n, m, w, b, g;
    cin >> n >> m >> w >> b >> g;
    G.resize(2 + n * m);
    int start = n * m;
    int end = start + 1;
    FOR(i, n){
    	scanf("%s", ma[i]);
    }
    pair<int, int> step[4] = { mp(0,1), mp(0,-1), mp(1, 0), mp(-1, 0)};
    FOR(i, n) FOR(j, m){
    	if(ma[i][j] == 'W'){
    		add_edGe(start, i * m + j, b);

    	} else {
    		add_edGe(i * m + j, end, w);
    	}
    	FOR(k, 4){
			int x = i + step[k].first;
			int y = j + step[k].second;
			if(x >= 0 && y >= 0 && x < n && y < m ){
				add_edGe(i * m + j, x * m + y, g);
			}
		}
    }
   cout <<  try_din(start ,end);
//    memset(used ,0, sizeof used);
//    dfs(start);
//    int val = 0;
//    FOR(i, sz(g)){
//    	for(auto ed : g[i]){
//    		if(used[i] != used[ed.to]){
//    			val +=
//    		}
//    	}
//    }
 }



