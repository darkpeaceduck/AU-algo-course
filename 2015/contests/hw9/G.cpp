
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
#define FORN(i, j, n) for(int i = (j); i <(n); i++)
#define all(a) (a).begin(), (a).end()
using namespace std;
#define DEB(...) fprintf(stderr, __VA_ARGS__)

//=======================
//#define pi 3.14159265358979323
#define eps 1e-9
#define INF 2e9
#define MN 2000000
#define SM 2000
//=====================================================


int main()
{
#ifdef MYLOCAL
    freopen("input.txt", "r", stdin);
 //   freopen("A9.out", "w", stdout);
#else
    freopen("cubes.in", "r", stdin);
    freopen("cubes.out", "w", stdout);
#endif
    int n, m;
    cin >> n >> m;
    vector<int> s(n);
    FOR(i, n){
    	scanf("%d", &s[i]);
    }
    vector<int> d2 (n);
    int l=0, r=-1;
    for (int i=0; i<n; ++i) {
    	int k = (i>r ? 0 : min (d2[l+r-i+1], r-i+1)) + 1;
    	while (i+k-1 < n && i-k >= 0 && s[i+k-1] == s[i-k])  ++k;
    	d2[i] = --k;
    	if (i+k-1 > r)
    		l = i-k,  r = i+k-1;
    }
    int last = -1;
    for(int i = n - 1; i >= 0; i--){
//    	if(i + d[1][i] + 1 == n){
//    		cout << i + 1 << " ";
//    		continue;
//    	}
    	if(i - d2[i] == 0){
    		cout << n - (d2[i]) << " ";
    	}
    }
};

