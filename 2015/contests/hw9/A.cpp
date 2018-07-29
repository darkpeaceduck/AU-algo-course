
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
#define MN 1000000
#define SM 2000
//=====================================================

vector<int> prefix_function (string &s) {
	int n = (int) s.length();
	vector<int> pi (n);
	for (int i=0; i<n; ++i)
		for (int k=0; k<=i; ++k)
			if (s.substr(0,k) == s.substr(i-k+1,k))
				pi[i] = k;
	return pi;
}
int main()
{
#ifdef MYLOCAL
    freopen("input.txt", "r", stdin);
 //   freopen("A9.out", "w", stdout);
#else
    freopen("unequal.in", "r", stdin);
    freopen("unequal.out", "w", stdout);
#endif
    string s;
    cin >> s;
    string t = "";
    int ans = 0;
    FOR(i, sz(s)){
    	t += s[i];
    	reverse(all(t));
    	vector<int> res = prefix_function(t);
    	reverse(all(t));
    	ans += sz(t) - *max_element(all(res));
    }
    cout << ans;
};

