
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
#define FORN(i, j, n) for(int i = (j); i < (n); i++)
#define all(a) (a).begin(), (a).end()
using namespace std;
#define DEB(...) fprintf(stderr, __VA_ARGS__)
//=======================
//#define pi 3.14159265358979323
#define eps 1e-9
#define INF 2e15
#define MN 1001
#define SM 2000
//=====================================================
const lo MAXN = 510;
lo n, g[MAXN][MAXN];
lo best_cost = INF;
vector<int> best_cut;

void mincut() {
	vector<int> v[MAXN];
	FOR(i, n){
		v[i] = {i};
	}
	lo w[MAXN];
	bool exist[MAXN], in_a[MAXN];
	memset (exist, true, sizeof exist);
	for (lo ph=0; ph<n-1; ++ph) {
		memset (in_a, false, sizeof in_a);
		memset (w, 0, sizeof w);
		for (lo it=0, prev; it<n-ph; ++it) {
			lo sel = -1;
			for (lo i=0; i<n; ++i)
				if (exist[i] && !in_a[i] && (sel == -1 || w[i] > w[sel]))
					sel = i;
			if (it == n-ph-1) {
				if (w[sel] < best_cost)
					best_cost = w[sel],  best_cut = v[sel];
				v[prev].insert (v[prev].end(), v[sel].begin(), v[sel].end());
				for (lo i=0; i<n; ++i)
					g[prev][i] = g[i][prev] += g[sel][i];
				exist[sel] = false;
			}
			else {
				in_a[sel] = true;
				for (lo i=0; i<n; ++i)
					w[i] += g[sel][i];
				prev = sel;
			}
		}
	}
}

int main()
{
#ifdef MYLOCAL
    freopen("input.txt", "r", stdin);
   // freopen("output.txt", "w", stdout);
#else
    freopen("stor.in", "r", stdin);
    freopen("stor.out", "w", stdout);
#endif
    int m;
    cin >> n >> m;
    FOR(i, m){
    	int a, b, c;
    	scanf("%d%d%d", &a, &b, &c);
    	a--;b--;
    	g[a][b] += c;
    	g[b][a] += c;
    }
    mincut();
    cout << best_cost << endl << sz(best_cut) << endl;
    for(auto to : best_cut){
    	printf("%d ", to + 1);
    }
}



