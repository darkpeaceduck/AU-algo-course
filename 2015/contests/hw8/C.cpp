
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
#define INF 2e9
#define MN 1010
#define SM 2000
//=====================================================

int a[MN][MN];
int ans[MN];
int vengry(int n){
	int m = n;
	vector<int> u (n+1), v (m+1), p (m+1), way (m+1);
	for (int i=1; i<=n; ++i) {
		p[0] = i;
		int j0 = 0;
		vector<int> minv (m+1, INF);
		vector<char> used (m+1, false);
		do {
			used[j0] = true;
			int i0 = p[j0],  delta = INF,  j1;
			for (int j=1; j<=m; ++j)
				if (!used[j]) {
					int cur = a[i0][j]-u[i0]-v[j];
					if (cur < minv[j])
						minv[j] = cur,  way[j] = j0;
					if (minv[j] < delta)
						delta = minv[j],  j1 = j;
				}
			for (int j=0; j<=m; ++j)
				if (used[j])
					u[p[j]] += delta,  v[j] -= delta;
				else
					minv[j] -= delta;
			j0 = j1;
		} while (p[j0] != 0);
		do {
			int j1 = way[j0];
			p[j0] = p[j1];
			j0 = j1;
		} while (j0);
	}
	for(int i = 1; i <= n; i++){
		ans[p[i]] = i;
	}
	return -v[0];
}

int main()
{
#ifdef MYLOCAL
    freopen("input.txt", "r", stdin);
   // freopen("output.txt", "w", stdout);
#else
    freopen("assignment.in", "r", stdin);
    freopen("assignment.out", "w", stdout);
#endif
    int n;
    cin >> n;
    FORN(i, 1, n + 1){
    	FORN(j, 1, n + 1){
    		cin >> a[i][j];
    	}
    }
    cout << vengry(n) << endl;
    FORN(i, 1, n + 1){
    	cout << i << " " << ans[i] << endl;
    }
}


