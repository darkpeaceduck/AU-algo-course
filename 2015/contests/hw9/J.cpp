
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

string get_p(const string &s){
	string res = "";
	int done = sz(s) - prefix_function(s).back();
	for(int i = 0; i < done; i++){
		res += s[i];
	}
	return res;
}

int main()
{
#ifdef MYLOCAL
    freopen("input.txt", "r", stdin);
 //   freopen("A9.out", "w", stdout);
#else
    freopen("2strings.in", "r", stdin);
    freopen("2strings.out", "w", stdout);
#endif
   string f, s;
   getline(cin, f);
   getline(cin, s);
   if(sz(f) < sz(s))
	   swap(f, s);
   vector<int> pp = prefix_function(s + " " + f);
   string ans;
   if( *max_element(all(pp)) == sz(s)){
	   ans = get_p(f);
   } else {
	   string val1 = get_p(f + s.substr(pp.back()));
	   string val2 = get_p(s + f.substr(prefix_function(f + " " + s).back()));
	   ans = (sz(val1) < sz(val2) ? val1 : val2);
   }
   cout << ans;
};

