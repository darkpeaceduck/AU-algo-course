
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
#define INF 2e9
#define MN 5010
#define SM 2000
//=====================================================

vector<pair<int, int> > g[MN];
int mt[MN];
int qmt[MN];
int remt[MN];
int used[MN];
int w1[MN];
int w2[MN];


pair<int, int> try_kuhn (int v ) {
	if (used[v])
		return mp(-INF, -INF);
	used[v] = true;
	pair<int, int> ret = mp(-INF, -INF);
	for(auto to : g[v]){
		if(mt[to.first] == -1){
			ret = max(ret, mp(w2[to.first], to.first));
		} else {
			ret = max(ret, try_kuhn (mt[to.first]));
		}
	}
	return ret;
}

bool dfs (int v, int fin, vector<pair<int, int> > &path) {
	if (used[v])
		return false;
	used[v] = true;
	for(auto to : g[v]){
		path.pb(to);
		if(mt[to.first] == -1){
			if(to.first == fin)
				return true;
		} else {
			if(dfs (mt[to.first], fin, path))
					return true;
		}
		path.pop_back();
	}
	return false;
}
int main()
{
#ifdef MYLOCAL
    freopen("input.txt", "r", stdin);
   // freopen("output.txt", "w", stdout);
#else
    freopen("matching.in", "r", stdin);
    freopen("matching.out", "w", stdout);
#endif
    int n ;
    int m ;
    int E;
    cin >> n >> m >> E;
    FOR(i, n){
    	cin >> w1[i];
    }
    FOR(i, m){
    	cin >> w2[i];
    }
    FOR(i, E){
    	int a, b;
    	scanf("%d%d", &a, &b);
    	a--;
    	b--;
    	g[a].pb(mp(b, i + 1));
    }
    vector<int> start(n);
    FOR(i, n){
    	start[i] = i;
    }
    sort(all(start), [](int a, int b){return w1[a] > w1[b] || (w1[a] == w1[b] && a < b);});
    memset(mt, -1, sizeof mt);
    int w = 0;
    FOR(q, n){
    	int val = -1;
    	pair<int, int> with;
    	memset(used, 0, sizeof used);
    	FOR(i1, n){
    		int i = start[i1];
    		if(remt[i])
    			continue;
    		pair<int, int> ret = try_kuhn(i);
    		int new_val = ret.first + w1[i] ;
    		if(new_val> val){
				val = new_val;
    			with = mp(i, ret.second);
    		}
    	}
    	if(val == -1)
    		break;
    	memset(used ,0 ,sizeof used);
    	vector<pair<int, int> > path = {mp(with.first, -1)};
    	dfs(with.first, with.second, path);
    	int cur = path[0].first;
    	w += val;
    	for(int i = 1; i < sz(path); i++){
    		int nx = mt[path[i].first];
    		mt[path[i].first] = cur;
    		qmt[path[i].first] = path[i].second;
    		remt[cur]++;
    		cur = nx;
    	}
    }


    vector<int> ans;
    FOR(i, m){
    	if(mt[i] != -1){
    		ans.pb(qmt[i]);
    	}
    }
    cout << w << endl << sz(ans) << endl;
    FOR(i, sz(ans)){
    	cout << ans[i] << " ";
    }
}



