
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
#define MN 1010
#define SM 52
//================================

char s[MN];
bitset<MN> c[MN];
int main()
{
#ifdef MYLOCAL
    freopen("input.txt", "r", stdin);
 //   freopen("A9.out", "w", stdout);
#else
    freopen("floyd32.in", "r", stdin);
    freopen("floyd32.out", "w", stdout);
#endif
    int n;
    cin >> n;

    FOR(i, n){
    	scanf("%s", &s);
    	FOR(j, n){
    		c[i][j] = s[j] == '1';
    	}
    }
    FOR(k, n) FOR(i, n){
    	if(c[i][k])
    		c[i] |= c[k];
    }
    FOR(i, n) {
    	FOR(j, n){
    		printf("%d", c[i][j] == 1);
    	}
    	printf("\n");
    }
};
