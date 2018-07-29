
#include <bits/stdc++.h>
#include <unordered_map>
#include <initializer_list>
#include <memory>
#include <vector>
#define mp make_pair
#define pb push_back
#define lo int
#define li long long int
#define db li

#define sz(a) (lo)(a).size()
#define FOR(i, n) for(int i = 0; i < (n); i++)
#define FORN(i, j, n) for(int i = (j); i <(n); i++)
#define all(a) (a).begin(), (a).end()
using namespace std;
#define DEB(...) fprintf(stderr, __VA_ARGS__)
//=======================
//======================
int readInt(){
	int temp;
	scanf("%d", &temp);
	return temp;
}

//=======================
//#define pi 3.14159265358979323
#define eps 1e-8
#define INF 2e9
#define MN 2010
#define SM 52
//================================

db Fabs(db a){
	if(a < 0)
		return -a;
	return a;
}

void gauss (vector < vector<db> > &a, vector<int> & money, vector<int> &q) {
	int n = (int) a.size();
	int m = (int) a[0].size();
	vector<int> where (m, -1);
	int row = 0;
	int cnt = 0;
	vector<int> ans;
	FOR(col, m){
		if(row >= n)
			break;
		int with = row;
		db Q = 1;
		for (int i=row; i<n; ++i){
			if (Fabs (a[i][col]) > Fabs (a[with][col]))
				with = i;
			if(a[i][col]){
				Q *= a[i][col];
			}
		}

		if (Fabs (a[with][col]) == 0)
			continue;

		FORN(i, col, m )
			swap (a[with][i], a[row][i]);
		for(int i = row; i < n; i++){
			if(a[i][col])
			FOR(j, m){
				a[i][j] *= Q / a[i][col];
			}
		}
		where[col] = row;
		cnt += money[col];
		ans.pb(q[col]);
		FOR(i, n)
			if (i != row && a[i][col]) {
				FORN(j, col, m )
					a[i][j] -= a[row][j] ;
			}
		++row;
	}
	if(row < n){
		cout << 0;
		return;
	}
	cout << cnt << endl;
	sort(all(ans));
	FOR(i, sz(ans)){
		cout << ans[i] + 1<< endl;
	}
}


int main()
{
#ifdef MYLOCAL
    freopen("input.txt", "r", stdin);
 //   freopen("A9.out", "w", stdout);
#else
    freopen("nikifor.in", "r", stdin);
    freopen("nikifor.out", "w", stdout);
#endif
    int m = readInt(), n = readInt();
    vector<vector<db> > kofi(n,vector<db>(m)), kof(n, vector<db>(m));
    FOR(i, m){
    	FOR(j, n){
    		int a= readInt();
    		kofi[j][i] = a;
    	}
    }
    vector<int> moneyi(m), money(m);
    FOR(i, m){
    	moneyi[i] = readInt();
    }
    vector<int> q(m); FOR(i, m) q[i] = i;
    sort(all(q), [&moneyi](int a, int b){ return moneyi[a] < moneyi[b] || (moneyi[a] == moneyi[b] && a < b);});
    FOR(i, m){
    	money[i] = moneyi[q[i]];
    	FOR(j, n){
    		kof[j][i] = kofi[j][q[i]];
    	}
    }
    gauss(kof, money, q);
};
