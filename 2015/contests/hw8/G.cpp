
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
#define MN 5010
#define SM 2000
//=====================================================

vector<int> g[MN], g2[MN];
int mt[MN];
int remt[MN];
int used[MN];
int used2[MN];
int is_path[MN];
bool try_kuhn (int v) {
	if (used[v])
		return false;
	used[v] = true;
	for(auto to : g[v]){
		if (mt[to] == -1 || try_kuhn (mt[to])) {
			mt[to] = v;
			return true;
		}
	}
	return false;
}


void dfs(int id){
	used[id]++;
	for(auto to : g[id]){
		used2[to]++;
		if(mt[to] != -1 && !used[mt[to]]){
			dfs(mt[to]);
		}
	}
}


void go(int id){
	used[id]++;
	FOR(i, sz(g[id])){
		int to = g[id][i];
		if(!used[to])
			go(to);
	}
}
int main()
{
#ifdef MYLOCAL
    freopen("input.txt", "r", stdin);
   // freopen("output.txt", "w", stdout);
#else
    freopen("hobbits.in", "r", stdin);
    freopen("hobbits.out", "w", stdout);
#endif
    int n;
    cin >> n;
    FOR(i, n) FOR(j, n){
    	int a;
    	scanf("%d", &a);
    	if(a){
    		g[i].pb(j);
    	}
    }

    FOR(i, n){
    	memset(used, 0, sizeof used);
    	go(i);
    	FOR(j, n){
    		if(i != j && used[j]){
    			g2[i].pb(j);
    		}
    	}
    }
    FOR(i, n){
    	swap(g[i], g2[i]);
    }

    memset(mt, -1, sizeof mt);
    int fl = 0;
    FOR(i, n){
    	memset(used, 0, sizeof used);
    	fl += try_kuhn(i);
    	is_path[i] = i;
    }

    FOR(i, n){
    	if(mt[i]!= -1)
    		remt[mt[i]] = 1;
    }
    memset(used, 0, sizeof used);
    FOR(i, n){
    	if(!used[i] && !remt[i] ){
    		dfs(i);
    	}
    }
    map<int, int> ans;
    FOR(i, n){
    	if(used[i])
    		ans[i + 1]++;
    	if(!used2[i])
    		ans[i + 1]++;
    }
    vector<int> rans;
    for(auto it : ans){
    	if(it.second == 2){
    		rans.pb(it.first);
    	}
    }
    cout << sz(rans) << endl;
    FOR(i, sz(rans))
    	cout << rans[i] << " ";
 }



