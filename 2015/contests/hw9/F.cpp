
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

int osn[MN];
int Hash[MN];
void build(const string &s){
	int osni = 997;
	int cur = 1;
	FOR(i, MN){
		cur *= osni;
		osn[i] = cur;
	}
	int ha = 0;
	FOR(i, sz(s)){
		ha += (s[i] + 1) * osn[i];
		Hash[i] = ha;
	}
}

int segm(int l, int r){
	return (Hash[r] - (l ? Hash[l -1] : 0)) * osn[MN - 1 - l];
}

int main()
{
#ifdef MYLOCAL
    freopen("input.txt", "r", stdin);
 //   freopen("A9.out", "w", stdout);
#else
    freopen("substrcmp.in", "r", stdin);
    freopen("substrcmp.out", "w", stdout);
#endif
    string s;
    cin >> s;
    build(s);
    int m;
    cin >> m;
    FOR(i, m){
    	int a, b, c, d;
    	scanf("%d%d%d%d", &a, &b, &c, &d);
    	a--;
    	b--;
    	c--;
    	d--;
//    	cout << Hash[b] << endl;
    	printf((b - a) == (d - c) && segm(a, b) == segm(c, d) ? "Yes\n" : "No\n");
    }
};

