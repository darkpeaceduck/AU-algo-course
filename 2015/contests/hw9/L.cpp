
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
#define MN 2000
#define SM 2000
//================================


int main()
{
#ifdef MYLOCAL
    freopen("input.txt", "r", stdin);
//    freopen("A9.out", "w", stdout);
#else
    freopen("trans.in", "r", stdin);
    freopen("trans.out", "w", stdout);
#endif
    int n;
    cin >> n;
    vector<int> val(n);
    FOR(i, n){
    	scanf("%d", &val[i]);
    }
    vector<int> p(n);
    for(int i = 1; i < n; i++){
    	for(int j = i + val[i] - 1; j >= i && !p[j]; j--){
    		p[j] = j - i + 1;
    	}
    }
    FOR(i, n){
    	printf("%d ", p[i]);
    }
};
