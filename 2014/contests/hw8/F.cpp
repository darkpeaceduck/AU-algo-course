
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

lo dp[MN][MN];
pair<lo, pair<lo, lo> > fr[MN][MN];
bool comp(char a, char b)
{
	return (a == '(' && b == ')') ||
	(a == '[' && b == ']') ||
	(a == '{' && b == '}');
}
void re(lo a, lo b, string &S)
{
//	printf("%d %d\n", a, b);
	lo ty = fr[a][b].first;
	lo f=  fr[a][b].second.first;
	lo s = fr[a][b].second.second;

	if(fr[a][b].first == 1)
	{
		re(a, f, S);
		re(f + 1, b, S);
		return;
	}

	if(comp(S[a] ,S[b]))
		cout << S[a];
	if(fr[a][b].first != -1)
	{
		re(f, s, S);
	}
	if(comp(S[a],S[b]))
		cout << S[b];
}
int main(){
#ifdef MYLOCAL
	 //freopen("perm.ou	t", "w", stdout);
	freopen("input.txt", "r", stdin);
#else
	freopen("erase.in", "r", stdin);
	freopen("erase.out", "w",stdout);
#endif
	string S;
	cin >> S;
	lo n = S.length();
	FOR(i, n) for(lo j = i; j < n; j++)
	{
		fr[i][j] = mp(-1, mp(-1, -1));
		dp[i][j] = comp(S[i], S[j]);
	}
	for(lo len = 2; len <= n; len++)
	{
		FOR(i, n)
		{
			if(i + len - 1 < n)
			{
				vector<char> open = { '(', '{', '['},
						     closed = {')', '}', ']'};
				map<char, vector<lo> > index;
				FOR(k, len )
				{
					index[S[i + k]].pb(i + k);
					if(k < len - 1 && dp[i][i + len - 1] < dp[i][i + k] + dp[i + k + 1][i + len - 1])
					{
						dp[i][i + len - 1] = dp[i][i + k] + dp[i + k + 1][i + len - 1];
						fr[i][i + len - 1] = mp(1, mp(i + k, -1));
					}
				}
				if(comp(S[i], S[i + len - 1]) && dp[i][i + len - 1] < dp[i + 1][i + len - 2] + 1)
				{
					dp[i][i + len - 1] = dp[i + 1][i + len - 2] + 1;
					fr[i][i + len - 1] = mp(0, mp(i + 1, i + len - 2));
				}
			}
		}
	}
//	cout << dp[0][n - 1];
	re(0, n - 1, S);
}

