
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


vector<int> prefix_function (const string &s) {
	int n = (int) s.length();
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

int dp[MN];
int last[MN];
int op[MN];
int can[MN];
int from[MN];

void build_can(string &s){
	int n = sz(s);
	FOR(i, n){
		string t = s.substr(i);
//		vector<int> p = prefix_function(t);
//		vector<int> mini(t.length(), -INF);
//		for(int j = 1; j < sz(p); j++){
//			mini[p[j]] = max(mini[p[j]], j);
//		}
//		for(int j = sz(mini) - 1; j > 0; j--){
//			mini[p[j - 1]] = max(mini[p[j- 1]], mini[j]);
//			int T = sz(mini) - j;
//			can[i + T - 1] = max(can[i + T - 1], mini[j]);
//		}

		vector<int> z = z_function(t);
		for(int j = 1; j < sz(z); j++){
			if(z[j] > can[i + j]){
				from[i + j] = i;
				can[i + j] = z[j];
			}
		}
	}
}

void re(int pos, string &s, int cnt){
	if(pos == -1){
		cout << cnt << endl;
		return;
	}
	int p = last[pos];
	re(p, s, cnt + 1);
	if(p == pos - 1){
		cout << s[pos];
	} else {
		cout << from[p + 1] + 1 << " " << pos - p;
	}
	cout << endl;
}
int main()
{
#ifdef MYLOCAL
    freopen("input.txt", "r", stdin);
 //   freopen("A9.out", "w", stdout);
#else
    freopen("archiver.in", "r", stdin);
    freopen("archiver.out", "w", stdout);
#endif
    string s;
    cin >> s;
    build_can(s);
    FOR(i, MN){
    	dp[i] = INF;
    }
    dp[0] = 1;
    last[0] = -1;
    for(int i = 1; i < sz(s); i++){
    	dp[i ] = dp[i - 1] + 1;
    	last[i] = i - 1;
    	for(int j = i - 2; j >= 0; j--){
    		if(can[j + 1] >= i - j){
    			if(dp[i] > dp[j] + 5){
    				dp[i]  = dp[j] + 5;
    				last[i] = j;
    			}
    		}
    	}
    }
    cout << dp[sz(s)- 1] << " ";
    re(sz(s) - 1, s, 0);
};

