
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
int g[MN];
int main()
{
#ifdef MYLOCAL
    freopen("input.txt", "r", stdin);
 //   freopen("A9.out", "w", stdout);
#else
    freopen("heaps2.in", "r", stdin);
    freopen("heaps2.out", "w", stdout);
#endif
    int n;
    cin >> n;
    vector<int> a(n);
    FOR(i, n){
    	scanf("%d", &a[i]);
    }
    sort(all(a));
    for(int i = 1; i < MN; i++){
    	color++;
    	FOR(j, n){
    		if(a[j] > i)
    			continue;
    		cnt[g[i - a[j]]] = color;
    	}
    	g[i] = mex();
    }
    int m;
    cin >> m;
    FOR(i, m){
    	int a;
    	scanf("%d", &a);
    	printf(g[a] ? "First\n" : "Second\n");
    }
};
