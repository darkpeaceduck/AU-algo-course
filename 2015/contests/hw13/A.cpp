
#include <bits/stdc++.h>
#include <unordered_map>
#include <initializer_list>
#include <memory>
#include <vector>
#define mp make_pair
#define pb push_back
#define lo int
#define li long long int
#define db long double

#define sz(a) (lo)(a).size()
#define FOR(i, n) for(int i = 0; i < (n); i++)
#define FORN(i, j, n) for(int i = (j); i <(n); i++)
#define all(a) (a).begin(), (a).end()
using namespace std;
#define DEB(...) fprintf(stderr, __VA_ARGS__)
//=======================
//======================
//=======================
//#define pi 3.14159265358979323
#define eps 1e-9
#define INF 2e9
#define MN 300010
#define SM 52
//================================

int gauss (vector < vector<db> > &a, vector<db> & ans) {
	int n = (int) a.size();
	int m = (int) a[0].size() - 1;

	vector<int> where (m, -1);
	ans.assign (m, 0);
	int row = 0;
	FOR(col, n){
		int with = row;
		for (int i=row; i<n; ++i)
			if (fabs (a[i][col]) > fabs (a[with][col]))
				with = i;
		if (fabs (a[with][col]) < eps)
			continue;
		FORN(i, col, m + 1)
			swap (a[with][i], a[row][i]);
		where[col] = row;
		FOR(i, n)
			if (i != row) {
				db c = a[i][col] / a[row][col];
				FORN(j, col, m + 1)
					a[i][j] -= a[row][j] * c;
			}
		++row;
	}

	FOR(i, m)
		if (where[i] != -1)
			ans[i] = a[where[i]][m] / a[where[i]][i];
	FOR(i, n){
		db sum = 0;
		FOR(j, m)
			sum += ans[j] * a[i][j];
		if (fabs (sum - a[i][m]) > eps)
			return 0;
	}

	FOR(i, m)
		if (where[i] == -1)
			return 2;
	return 1;
}


int main()
{
#ifdef MYLOCAL
    freopen("input.txt", "r", stdin);
 //   freopen("A9.out", "w", stdout);
#else
    freopen("linear.in", "r", stdin);
    freopen("linear.out", "w", stdout);
#endif
    int n;
    cin >> n;
    vector<vector<db>> kof(n, vector<db>(n + 1));
    FOR(i, n){
    	FOR(j, n + 1){
    		scanf("%Lf", &kof[i][j]);
    	}
    }
    vector<db> ans;
    int res = gauss(kof, ans);
    if(!res){
    	cout << "impossible";
    	return 0;
    }
    if(res == 2){
    	cout << "infinity";
    	return 0;
    }
    cout << "single" << endl;
    FOR(i, sz(ans)){
    	printf("%.10Lf ", ans[i]);
    }
};
