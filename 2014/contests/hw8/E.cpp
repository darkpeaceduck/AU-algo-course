
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
#define li unsigned long long int
#define db double
#define pb push_back
#define FOR(i, n) for(lo (i) = 0; (i) < (n); (i)++)
//#define all(a) (a).begin(), (a).end()
#define DEB(...) fprintf(stderr,__VA_ARGS__)
#define pi 3.14159265358979323
//#define eps 1e-3
#define MN 501
#define sz(n) (lo) (n).size()
#define SM 40
const li INF = 2e12;


using namespace std;

lo lcp[MN][MN];
lo dp[MN][MN];
pair<lo, lo> fr[MN][MN];
string tostring(lo a)
{
	stringstream ss;
	ss << a;
	string outp;
	ss >> outp;
	return outp;
}
void re(lo a, lo b, string &s)
{
//	printf("%d %d\n", a, b);
	if(fr[a][b].first == -1)
	{
		for(; a <= b; a++)
			cout << s[a];
		return;
	}
	lo ty =fr[a][b].first;
	lo p = fr[a][b].second;
	if(!ty)
	{
		re(a, p, s);
		re(p + 1, b, s);
	}
	else
	{
		cout << tostring(p) << "(";
		re(a, a + (b - a + 1) / p - 1, s);
		cout << ")";

	}
}
int main(){
#ifdef MYLOCAL
	 //freopen("perm.ou	t", "w", stdout);
	freopen("input.txt", "r", stdin);
#else
	freopen("folding.in", "r", stdin);
	freopen("folding.out", "w",stdout);
#endif
	string s;
	cin >> s;
	lo n = s.length();
	FOR(i, n) FOR(j, n) for(lo k = 0; k + max(i, j) < n; k++)
	{
		if(s[i + k] != s[j + k])
			break;
		lcp[i][j]++;
	}
	FOR(i, n) for(lo j = i; j < n; j++)
	{
		fr[i][j] = mp(-1, -1);
		dp[i][j] = j - i + 1;
	}
	for(lo len = 1; len <= n; len++)
	{
		FOR(i, n)
		{
			if(i + len - 1 < n)
			{
				FOR(k, len - 1)
				{
					if(dp[i][i + k] + dp[i + k + 1][i + len - 1] < dp[i][i + len - 1])
					{
						dp[i][i + len - 1] = dp[i][i + k] + dp[i + k + 1][i + len - 1];
						fr[i][i + len - 1] = mp(0, i + k);
					}
				}
				for(lo q = i + len; q < n; q += len)
				{

					if(lcp[i][q] < len)
						break;
					lo add_numb = (q - i) / len + 1;
					string add = tostring(add_numb);

					if(dp[i][i + len - 1] + 2 + add.length() < dp[i][q + len - 1])
					{
						dp[i][q + len - 1] = dp[i][i + len - 1] + 2 + add.length();
						fr[i][q + len - 1] = mp(1, add_numb);
					}
				}
			}
		}
	}
	re(0, n - 1, s);
}

