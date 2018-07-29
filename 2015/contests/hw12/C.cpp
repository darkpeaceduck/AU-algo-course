
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

//#define sz(a) (lo)(a).size()
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
#define MN 1000010
#define SM 52
//================================
int cnt[MN];
int color = 1;
int mex(){
	for(int i = 0;; i++){
		if(cnt[i] != color)
			return i;
	}
}
int g[1010][1010][2];
int main()
{
#ifdef MYLOCAL
    freopen("input.txt", "r", stdin);
 //   freopen("A9.out", "w", stdout);
#else
    freopen("heaps.in", "r", stdin);
    freopen("heaps.out", "w", stdout);
#endif
    int A, B;
    cin >> A >> B;
    vector<vector<int> > a(2);
    FOR(k, 2){
		int n;
		cin >> n;
		a[k].resize(n);
		FOR(i, n){
			scanf("%d", &a[k][i]);
		}
    }
    FOR(i, A + 1) FOR(j, B + 1) FOR(k, 2){
    	color++;
    	for(auto to : a[k]){
    		if(i >= to){
    			cnt[g[i - to][j][1 - k]] = color;
    		}
    		if(j >= to){
    			cnt[g[i][j - to][1 - k]] = color;
    		}
    	}
    	g[i][j][k] = mex();
    }
    cout << (g[A][B][0] ? "First\n" : "Second\n");
};
