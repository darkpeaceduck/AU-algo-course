
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
#define MN 2010
#define SM 52
//================================

void print(vector < bitset<MN> > &a){
	int n = sz(a);
	FOR(i, n){
	    	FOR(j, n + 1){
	    		int b = a[i][j];
	    		printf("%d", b);
	    	}
	    	printf("\n");
	    }

}
int gauss (vector < bitset<MN> > a, vector< int > & ans) {
	int n = (int) a.size();
	int m = n + 1;
	vector<int> where (m, -1);
	int row = 0;
	FOR(col, n){
		int with = row;
		for (int i=row; i<n; ++i)
			if (a[i][col]){
				with = i;
				break;
			}
		if(!a[with][col])
			continue;
		swap(a[with], a[row]);
		where[col] = row;
		FOR(i, n){
			if (i != row && a[i][col]) {
				a[i] ^= a[row];
			}
		}
		++row;
	}

	ans.assign(n, 0);
	FOR(i, n){
		if(where[i] != -1)
			ans[i] = a[where[i]][n];
	}
	FOR(i, n){
		int sum = 0;
		FOR(j, n)
			sum += ans[j] * a[i][j];
		if (sum % 2!= a[i][n])
			return 0;
	}
	return 1;
}


int main()
{
#ifdef MYLOCAL
    freopen("input.txt", "r", stdin);
 //   freopen("A9.out", "w", stdout);
#else
    freopen("puzzle.in", "r", stdin);
    freopen("puzzle.out", "w", stdout);
#endif
    int n;
    cin >> n;
    vector<bitset<MN> > kof(n);
    FOR(i, n){
    	int m;
    	scanf("%d", &m);
    	FOR(j, m){
    		int a;
    		scanf("%d", &a);
    		--a;
    		kof[a][i] = 1;
    	}
    }
    FOR(i, n){
    	int t;
    	scanf("%d", &t);
    	kof[i][n] = t;
    }
    vector<int> ans(n);
    int res = gauss(kof, ans);
    if(!res){
		FOR(i, n){
			kof[i][n] = 1 - kof[i][n];
		}
		res = gauss(kof, ans);
    }
    if(!res){
		cout << -1;
		return 0;
	}
    cout << count(ans.begin(), ans.end(), 1) << endl;
    FOR(i ,sz(ans)){
    	if(ans[i]){
    		printf("%d ", i + 1);
    	}
    }
};
