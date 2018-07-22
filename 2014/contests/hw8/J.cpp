
///#pragma comment(linker, "/STACK:100000000000000")
#include <stdio.h>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <stack>
#include <queue>
#include <bitset>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string.h>
#include <cctype>

#include <cassert>


#include <ctime>
//#include <unordered_set>
//expr
/*#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
*/
//

#define mp make_pair
#define pb push_back
#define lo int
#define li long long int
#define db double
#define pb push_back
#define FOR(i, n) for(lo (i) = 0; (i) < (n); (i)++)
//#define all(a) (a).begin(), (a).end()
#define DEB(...) fprintf(stderr,__VA_ARGS__)
#define pi 3.14159265358979323
//#define eps 1e-3
#define MN 5010
#define sz(n) (lo) (n).size()
#define SM 40
const li INF = 2e9;


using namespace std;

int dp[2][MN];
inline void relax(lo toa, lo tob, lo val, lo type)
{
	if(dp[toa][tob] < val)
	{
		dp[toa][tob] = val;
	}
}

int *Nwcount(string f, string s)
{
	lo n = f.length();
	lo m = s.length();
	memset(dp, 0, sizeof dp);
	lo cur = 0;
	FOR(i, n + 1)
	{
		lo nex = (cur + 1) % 2;
		memset(dp[nex], 0, sizeof dp[nex]);
		FOR(j, m + 1)
		{
			relax(cur, j + 1, dp[cur][j], 1);
			relax(nex, j, dp[cur][j], 2);
			if(f[i] == s[j])
				relax(nex, j + 1, dp[cur][j] + 1, 3);
		}
		cur = nex;
	}
	/*for(lo i = 1; i <= m; i++)
	{
		dp[cur][i - 1] = dp[cur][i];
	}
	*/
//	cout << "NW " << f << " " << s << " ";
//	FOR(i, m + 1)
//	{
//		cout << dp[cur][i] << " ";
//	}
//	cout << endl;
	cur = (cur + 1) % 2;
	int *ret = new int[m + 1];
	FOR(i, m + 1)
		ret[i] = dp[cur][i];
	return ret;
}

string rev(string s)
{
	reverse(s.begin(), s.end());
	return s;
}
string hirshberg(string f, string s)
{
//	cout << "in " << f << " " << s  << endl;
	if(sz(f) == 0)
		return string("");
	if(sz(s) == 0)
		return string("");
	if(sz(f) == 1)
	{
		FOR(i, sz(s))
		{
			if(s[i] == f[0])
				return string("") + f[0];
		}
		return string("");
	}
	if(sz(s) == 1)
	{
		FOR(i, sz(f))
		{
			if(f[i] == s[0])
				return string("") + s[0];
		}
		return string("");
	}
	lo xlen = f.length();
	lo xmid = xlen / 2;
	lo ylen = s.length();
	int * ScoreL = Nwcount(f.substr(0, xmid), s);
	int * ScoreR = Nwcount(rev(f.substr(xmid, xlen - xmid)), rev(s));
//	FOR(i, sz(s) + 1)
//		cout << ScoreL[i] << " ";
//	cout << endl;
//	FOR(i, sz(s) + 1)
//		cout << ScoreR[i] << " ";
//	cout << endl;
	//	DEB("scorecomli");
	int ymid = 0;
	int maxval = -1;
	FOR(i, sz(s) + 1)
	{
		if(ScoreL[i] + ScoreR[sz(s) - i] > maxval)
		{
			maxval = ScoreL[i] + ScoreR[sz(s) - i];
			ymid = i;
		}
	}
	delete[] ScoreL;
	delete[] ScoreR;
//	cout << ymid << " " << maxval<< endl;
	string res =  hirshberg(f.substr(0, xmid), s.substr(0, ymid)) +
			hirshberg(f.substr(xmid, xlen - xmid), s.substr(ymid, ylen - ymid));
//	cout << "out " << f << " " << s << " " << res << endl;
 	return res;
}

int main(){
#ifdef MYLOCAL
	 //freopen("perm.ou	t", "w", stdout);
	freopen("input.txt", "r", stdin);
#else
	freopen("subseq.in", "r", stdin);
	freopen("subseq.out", "w",stdout);
#endif
	string f, s;
	cin >> f >> s;
	cout << hirshberg(f, s);
}
