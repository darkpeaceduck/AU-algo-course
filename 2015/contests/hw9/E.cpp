
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

vector<int> prefix_function (char * s, int n) {
	vector<int> pi (n);
	for (int i=1; i<n; ++i) {
		int j = pi[i-1];
		while (j > 0 && s[i] != s[j])
			j = pi[j-1];
		if (s[i] == s[j])  ++j;
		pi[i] = j;
	}
	return pi;
}
vector<int> z_function (const string &s) {
	int n = (int) s.length();
	vector<int> z (n);
	for (int i=1, l=0, r=0; i<n; ++i) {
		if (i <= r)
			z[i] = min (r-i+1, z[i-l]);
		while (i+z[i] < n && s[z[i]] == s[i+z[i]])
			++z[i];
		if (i+z[i]-1 > r)
			l = i,  r = i+z[i]-1;
	}
	return z;
}

char s[MN], t[MN];
int main()
{
#ifdef MYLOCAL
    freopen("input.txt", "r", stdin);
 //   freopen("A9.out", "w", stdout);
#else
    freopen("decimal.in", "r", stdin);
    freopen("decimal.out", "w", stdout);
#endif
    scanf("%s", s);
    int n = strlen(s);
    for(int i = n - 1; i >=0;i--){
    	t[n - 1- i ] = s[i];
    }
    int mini = INF;
    int a, b;
    vector<int> p = prefix_function(t, n - 2);
    FOR(i, n - 2){
    	int aa = i + 1 - p[i];
    	int bb = (n - 2) - (i + 1);
    	if(aa + bb < mini){
    		mini = aa + bb;
    		a = aa;
    		b = bb;
    	}
    }
    cout << s[0] << s[1];
    FOR(i, b){
    	printf("%c", s[2 + i]);
    }
    cout << "(";
    FOR(i, a){
    	printf("%c", s[2 + b + i]);
    }
    cout << ")";
};

